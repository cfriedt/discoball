#include <stdio.h>
#include <signal.h>
#include <stdbool.h>

#include <pthread.h>

#include "discoball/discoball.h"
#include "discoball/tcpip-pthread/server.h"

discoball_context_t ctx;

static pthread_mutex_t ok_to_exit_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t ok_to_exit_cond = PTHREAD_COND_INITIALIZER;
static bool ok_to_exit;

static void sig_handler( int sig ) {
	int r;

	static bool sig_caught;

	if ( sig_caught ) {
		return;
	}
	sig_caught = true;
	printf( "received signal %d\n", sig );

	r = discoball_server_deregister( &ctx );
	if ( 0 != r ) {
		printf( "discoball_server_deregister returned %d\n", r );
	}

	pthread_mutex_lock( &ok_to_exit_mutex );
	ok_to_exit = true;
	pthread_cond_signal( &ok_to_exit_cond );
	pthread_mutex_unlock( &ok_to_exit_mutex );
}

int main( int argc, char *argv[] ) {
	int r;
	bool exit_ok;

	signal( SIGHUP, sig_handler );
	signal( SIGINT, sig_handler );
	signal( SIGQUIT, sig_handler );

	r = discoball_server_register( &ctx, (discoball_server_cb_t *)&discoball_tcpip_pthread_server_cb );
	if ( 0 != r ) {
		printf( "discoball_server_register returned %d\n", r );
		goto out;
	}

	pthread_mutex_lock( &ok_to_exit_mutex );
	for( exit_ok = ok_to_exit; ! exit_ok; exit_ok = ok_to_exit ) {
		pthread_cond_wait( &ok_to_exit_cond, &ok_to_exit_mutex );
	}
	pthread_mutex_unlock( &ok_to_exit_mutex );

out:
	return r;
}
