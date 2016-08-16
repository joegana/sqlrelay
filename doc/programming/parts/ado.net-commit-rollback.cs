using System;
using SQLRClient;
using System.Data;
using System.IO;

namespace SQLRExamples
{
	class SQLRExample
	{
		public static void Main()
		{
			SQLRelayConnection sqlrcon = new SQLRelayConnection("Data Source=sqlrserver:9000;User ID=test;Password=test;Retry Time=0;Tries=1;Debug=false");
			sqlrcon.Open();

			SQLRelayTransaction sqlrtran = sqlrcon.BeginTransaction();

			... run some queries that we want to keep the results of ...

			sqlrtran.Commit();

			... run some queries that we don't want to keep the results of ...

			sqlrtran.Rollback();
		}
	}
}
