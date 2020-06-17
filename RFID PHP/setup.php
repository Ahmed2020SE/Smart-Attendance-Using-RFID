<?php
// John Longworth December 2016

$servername = "localhost";
$username = "root";
$password = "";
$dbname = "test";

// Connect to mysql server
$conn = mysql_pconnect($servername,$username,$password) 
  or die("Connection failed! ".mysql_error());
// Select database
mysql_select_db($dbname,$conn) 
  or die ("Database selection failed! ".mysql_error());    
  
$sql = "DROP TABLE IF EXISTS writeread";
$result = mysql_query($sql)
  or die("Invalid query 1: ".mysql_error());    
  
$sql = "CREATE TABLE writeread (logdata datetime,field varchar(20),value bigint(20))";
$result = mysql_query($sql)
  or die("Invalid query 2: ".mysql_error());  

$sql = "INSERT INTO writeread (logdata, field, value) VALUES ('2017-01-01 06:30:10','25','62')";
$result = mysql_query($sql)
  or die("Invalid query 3: ".mysql_error());   

$sql = "SELECT * FROM writeread";
$result = mysql_query($sql)
  or die("Invalid query 4: ".mysql_error());     
  
echo "Table created successfully.";  

$num_rows = mysql_num_rows($result);  
if ($num_rows > 0) {  
  echo "<table border='2'><tr><th>Log Date</th><th>Field</th><th>Value</th></tr>";
  while ($row = mysql_fetch_assoc($result)) {  
    echo "<tr>";
    echo "<td>".$row['logdata']."</td>";
    echo "<td>".$row['field']."</td>";
    echo "<td>".$row['value']."</td>";
    echo "</tr>";
  }  
echo "</table>";     
echo "Number of rows = ".$num_rows;
}  
  
mysql_close($conn);
?>
