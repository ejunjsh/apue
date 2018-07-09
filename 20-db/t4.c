#include "apue.h"
#include "apue_db.h"
#include <fcntl.h>

int
main(void)
{
	DBHANDLE	db;

	if ((db = db_open("db4", O_RDWR | O_CREAT | O_TRUNC,
	  FILE_MODE)) == NULL)
		err_sys("db_open error");

	if (db_store(db, "Alpha", "data1", DB_INSERT) != 0)
		err_quit("db_store error for alpha");
	if (db_store(db, "beta", "Data for beta", DB_INSERT) != 0)
		err_quit("db_store error for beta");
	if (db_store(db, "gamma", "record3", DB_INSERT) != 0)
		err_quit("db_store error for gamma");
	if (db_store(db, "test4", "test4", DB_INSERT) != 0)
		err_quit("db_store error for test4");
	if (db_delete(db, "test4")!=0)
		err_quit("db_delete error");
	if (db_delete(db, "gamma")!=0)
		err_quit("db_delete error");
	if (db_delete(db, "Alpha")!=0)
		err_quit("db_delete error");
	db_close(db);
	exit(0);
}
