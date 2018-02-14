SQLRelayCommand sqlrcom = (SQLRelayComand)sqlrcon.CreateCommand();
sqlrcom.CommandText = "begin exampleproc(:in1,:in2,:in3,:out1,:out2,:out3); end;";
sqlrcom.Parameters.Add("in1",1);
sqlrcom.Parameters.Add("in2",1.1);
sqlrcom.Parameters.Add("in3","hello");
SQLRelayParameter out1 = new SQLRelayParameter();
out1.ParameterName = "out1";
out1.Direction = ParameterDirection.Output;
out1.DbType = DbType.Int64;
sqlrcom.Parameters.Add(out1);
SQLRelayParameter out2 = new SQLRelayParameter();
out2.ParameterName = "out2";
out2.Direction = ParameterDirection.Output;
out2.DbType = DbType.Double;
sqlrcom.Parameters.Add(out2);
SQLRelayParameter out2 = new SQLRelayParameter();
out3.ParameterName = "out3";
out3.Direction = ParameterDirection.Output;
out3.DbType = DbType.String;
out3.Size = 20;
sqlrcom.Parameters.Add(out3);
sqlrcom.ExecuteNonQuery();
Int64 result1 = Convert.ToInt64(out1.Value);
Double result2 = Convert.ToDouble(out2.Value);
String result3 = Convert.ToString(out3.Value);
