/*
 * lmdbtest.cpp
 *
 *  Created on: 18 Apr 2018
 *      Author: junior
 */

#include <stdio.h>
#include <string>
#include <lmdb.h>
#include <map>

using namespace std;
int main (int argc, char* argv[]){

	int rc;
	MDB_env *env;
	MDB_dbi dbi;
	MDB_val key, data;
	MDB_txn *txn;
	MDB_cursor *cursor;
	map<int, int> dt;
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
		string k((char *)key.mv_data);
		k = k.substr(0, key.mv_size);
		printf("Size: %ld \tData: %s\n\n", key.mv_size, k.c_str());

		string v((char *)data.mv_data);
		v = v.substr(0, data.mv_size);
		printf("DATA\n");
		printf("Size: %ld \tData: %s\n\n", data.mv_size, v.c_str());
		dt[stoi(k)] = stoi(v);
		i++;
	}

	for(map<int, int>::iterator it = dt.begin(); it != dt.end(); it++){
		int key = it->first;
		int value = it->second;

		printf("%d, %d\n", key, value);
	}
	mdb_cursor_close(cursor);
	mdb_txn_abort(txn);
	mdb_close(env, dbi);
	mdb_env_close(env);
	return 0;
}
