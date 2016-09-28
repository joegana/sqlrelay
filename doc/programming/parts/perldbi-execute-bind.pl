#!/usr/bin/env perl

use DBI;

my $dbh=DBI->connect("DBI:SQLRelay:host=sqlrserver;port=9000;socket=/tmp/test.socket;tries=0;retrytime=1;debug=0","testuser","testpassword");

my $sth=$dbh->prepare("select * from my_table where col1=:0 and col2=:1 and col3=:2");

$sth->execute(undef,"hello",1,5.5);

... process the result set ...

$dbh->disconnect;
