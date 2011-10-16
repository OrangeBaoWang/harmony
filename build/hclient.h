/*
 * Copyright 2003-2011 Jeffrey K. Hollingsworth
 *
 * This file is part of Active Harmony.
 *
 * Active Harmony is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Active Harmony is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Active Harmony.  If not, see <http://www.gnu.org/licenses/>.
 */

/******************************
 * This is the header file for the client side of harmony.
 * 
 * Author: Cristian Tapus
 * History:
 *   July 9, 2000 - first version
 *   July 15, 2000 - comments and update added by Cristian Tapus
 *   Nov  20, 2000 - some changes made by Dejan Perkovic
 *   Dec  20, 2000 - comments and updates added by Cristian Tapus
 *   2010 : fix for multiple server connection by George Teodoro
 *   2004-2010 : various fixes and additions by Ananta Tiwari
 *******************************/

#ifndef __HCLIENT_H__
#define __HCLIENT_H__

/***
 * include other headers
 ***/

#include <sys/file.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#include "hutil.h"
#include "hmesgs.h"
#include "hsockutil.h"

/***
 * macro definition
 ***/

/*
 * the size of the buffer used to transfer data between server and client
 */
#define BUFFER_SIZE 1024
#define MAX_VAR_NAME BUFFER_SIZE

/*
 * define truth values
 */
#define false 0
#define true 1


/***
 * function definitions
 ***/

/*
 * When a program registers with the harmony server it uses this function
 *
 * Parms:
 *  use_sigs (int) - the client will use signals if the value is 1
 *		     the client will use polling if the value is 0
 * 		     the client will use sort of a polling if value is 2
 *  relocated (int)-
 *  sport (int)    - the port of the server 
 *  shost (char *) - the host of the server
 * Return:
 * integer
 */
int harmony_startup(int sport=0, char *shost=NULL, int use_sigs=0, int relocated=0);

/*
 * When a program announces the server that it will end it calls this
 * function
 * Params:
 * 
 * Return
 None
 */
void harmony_end(int socketIndex=0);

int harmony_get_client_id(int socketIndex=0);

/*
 * Inform the Harmony server of the bundles and requirements of the application
 */
void harmony_application_setup(char *description, int socketIndex=0);

void harmony_application_setup_file(char *fname, int socketIndex=0);

/*
 * Bind a local variable with a harmony bundle 
 */
void * harmony_add_variable(char *appName, char *bundleName, int type, 
                            int socketIndex=0, int local=0);


/*
 * Send to the server the value of a bound variable
 */
void harmony_set_variable(void *variable, int socketIndex = 0);


/*
 * Update bound variables on server'side.
 */
void harmony_set_all(int socketIndex=0);


/*
 * Get the value of a bound variable
 *
 * I decided to remove the function from the API since I want the user to
 * use the request_all function that plays the role of a barrier
 */
void * harmony_request_variable(char *variable, int socketIndex=0);


/*
 * Get the current value of all the bound variables
 */
int harmony_request_all(int socketIndex=0, int pull=0);

/*
 * Send the performance function result to the harmony server
 */
// int metric
void harmony_performance_update(int value, int socketIndex=0);
// double metric
void harmony_performance_update(double value, int socketIndex=0);


void* harmony_request_tcl_variable(char *variable, int socketIndex=0);

char* harmony_get_best_configuration(int socketIndex=0);

int harmony_check_convergence(int socketIndex=0);

int code_generation_complete(int socketIndex=0);

int harmony_code_generation_complete(int socketIndex=0);

void* harmony_database_lookup(int socketIndex=0);

void harmony_psuedo_barrier(int socketIndex=0);


/*
 * Get the prefix directory paths for .so files 
 */
char* harmony_get_config_variable(const char *, int socketIndex=0);

#endif /* __HCLIENT_H__ */







