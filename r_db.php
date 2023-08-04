<!DOCTYPE html>
<html>
	<head>
		<style>
			table {
				border-collapse: collapse;
				width: 100%;
				color: #1f5380;
				font-family: monospace;
				font-size: 20px;
				text-align: left;
			}
			th {
				background-color: #1f5380;
				color: white;
			}
			tr:nth-child(even) {background-color: #f2f2f2}
		</style>
	</head>
	<?php
		//Creates new record as per request
		//Connect to database
		$servername = "localhost";
		$database = "ukur_air";
		$username = "root";
		$password = "";


		$conn = mysqli_connect($servername, $username, $password, $database);

		    // Check connection
		    if (!$conn) {
		        die("Database Connection failed: " . mysqli_connect_error);
		    }?>
	<body>
		<table>
			<tr>
				<th>No</th>
				<th>Nama karyawan</th>
				<th>Jumlah Toluene (mL)</th>
				<th>Tanggal</th>
				<th>Waktu</th>
			</tr>
			<?php
				$table = mysqli_query($conn, "SELECT No, nm_karyawan, jumlah_air, Date, Time FROM tb_pengambilan_air"); //nodemcu_ldr_table = Youre_table_name
				while($row = mysqli_fetch_array($table))
				{


			?>
			<tr>
				<td><?php echo $row["No"]; ?></td>
				<td><?php echo $row["nm_karyawan"]; ?></td>
				<td><?php echo $row["jumlah_air"]; ?></td>
				<td><?php echo $row["Date"]; ?></td>
				<td><?php echo $row["Time"]; ?></td>
			</tr>
			<?php
				}
			?>
		</table>
	</body>
</html>
