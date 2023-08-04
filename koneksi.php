<php
$servername = "localhost";
$database = "ukur_air";
$username = "root";
$password = "";


$conn = mysqli_connect($servername, $username, $password, $database);

    // Check connection
    if (!$conn) {
        die("Database Connection failed: " . mysqli_connect_error);
    }
?>
