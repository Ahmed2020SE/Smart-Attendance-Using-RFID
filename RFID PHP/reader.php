<?php
// John Longworth December 2016 
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "test";
$field = $_GET['field'];
// Connect to mysql server
$conn = mysqli_connect($servername,$username,$password ) 
  or die("Connection failed! ".mysqli_error($conn));

// Select database
mysqli_select_db($conn,$dbname) 
  or die ("Database selection failed! ".mysqli_error($dbname));  
// Getting the field from the DB
$sql = "SELECT field FROM writeread WHERE field='".$field."'";
$result = mysqli_query($conn,$sql)
  or die("Invalid query: ".mysqli_error($sql));  
$num_rows = mysqli_num_rows($result);  

if ($num_rows > 0) {  
  /*echo "<table border='2'><tr><th>Log Date</th><th>Field</th><th>Value</th></tr>";
  while ($row = mysqli_fetch_assoc($result)) {  
    echo "<tr>";
    echo "<td>".$row['logdata']."</td>";
    echo "<td>".$row['field']."</td>";
    echo "<td>".$row['value']."</td>";
    echo "</tr>";
  }  
echo "</table>";*/     
echo "Number of rows = ".$num_rows;
} 
else {
  echo ("No rows returned");
}  

mysqli_close($conn);

?>