/*
 * Copyright 2012 Howard Chu, Symas Corp.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted only as authorized by the OpenLDAP
 * Public License.
 *
 * A copy of this license is available in the file LICENSE in the
 * top-level directory of the distribution or, alternatively, at
 * <http://www.OpenLDAP.org/license.html>.
 */
#include <stdio.h>
#include <string.h>
#include "lmdb.h"


int main(int argc,char * argv[])
{
	int rc;
	MDB_env *env;
	MDB_dbi dbi;
	MDB_val key, data;
	MDB_txn *txn;
	MDB_cursor *cursor;
	//map<int, int> dt;
	const char *name = argv[1];

	rc = mdb_env_create(&env);
	rc = mdb_env_open(env, name, 0, 0664);
	rc = mdb_txn_begin(env, NULL, MDB_RDONLY, &txn);
	rc = mdb_dbi_open(txn, NULL, 0, &dbi);
	rc = mdb_cursor_open(txn, dbi, &cursor);
	int i = 1;
	while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT)) == 0) {
		printf("*******************************************************************************************\niteration %d\n", i);

		printf("KEY\n");
		//char *k = substr((char *)key.mv_data, 0, key.mv_size);
		char k[32];
		strncpy(k, (char *)key.mv_data, key.mv_size);
		k[key.mv_size] = '\0';
		printf("Size: %ld \tData: %s\n\n", key.mv_size, k);

		//char v = substr((char *)data.mv_data, 0, data.mv_size);
		char v[32];
		strncpy(v, (char *)data.mv_data, data.mv_size);
		v[data.mv_size] = '\0';
		printf("DATA\n");
		printf("Size: %ld \tData: %s\n\n", data.mv_size, v);

		i++;
	}

	mdb_cursor_close(cursor);
	mdb_txn_abort(txn);
	mdb_close(env, dbi);
	mdb_env_close(env);
	return 0;
}
