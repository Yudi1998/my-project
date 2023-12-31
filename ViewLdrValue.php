<!DOCTYPE html>
<html>
	<head>
		<title>NodeMCU ESP8266 MySQL Database</title>
		<meta charset="utf-8">
	
		<script src="jquery.min.js"></script>
		<script>
			$(document).ready(function() {
				setInterval(function(){get_data()},5000);
				function get_data()
				{
					jQuery.ajax({
						type:"GET",
						url: "r_db.php",
						data:"",
						beforeSend: function() {
						},
						complete: function() {
						},
						success:function(data) {
							$("table").html(data);
						}
					});
				}
			});
		</script>
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
	<body>
		<h1 align="center" style="color:#1f5380;">Tabel pengambilan Toluene</h1>
		<table>
			<tr>
				<th>No</th> 
				<th>Nama karyawan</th>
				<th>Jumlah toluene (mL)</th> 
				<th>Tanggal</th>
				<th>Waktu</th>
			</tr>
		</table>
	</body>
</html>
