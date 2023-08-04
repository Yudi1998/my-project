<?php

$servername = "localhost";
$database = "ukur_air";
$username = "root";
$password = "";


$conn = mysqli_connect($servername, $username, $password, $database);

    // Check connection
    if (!$conn) {
        die("Database Connection failed: " . mysqli_connect_error);
    }


    //Get current date and time
    date_default_timezone_set('Asia/Jakarta');
    $d = date("Y-m-d");
    $t = date("H:i:s");


    if(!empty($_POST['flowMilliLitres']))
    {
		$flowMilliLitres = $_POST['flowMilliLitres'];
	    $sql = "INSERT INTO tb_pengambilan_air (jumlah_air, Date, Time) VALUES ('".$flowMilliLitres."', '".$d."', '".$t."')"; //nodemcu_ldr_table = Youre_table_name

		if ($conn->query($sql) === TRUE) {
		    echo "OK";
		} else {
		    echo "Error: " . $sql . "<br>" . $conn->error;
		}
	}


	$conn->close();
?>
