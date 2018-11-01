<!DOCTYPE html>
<html lang="en">
<head>
  <title>Smart Parking</title>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link href="https://fonts.googleapis.com/css?family=Poor+Story" rel="stylesheet">
  <link rel="stylesheet" href="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.0/jquery.min.js"></script>
  <script src="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js"></script>

<style>
	.red-icon {
		color:#ff0000;
	}
	.green-icon {
		color:#009933;
	}
	.table-responsive
	{
		width:100%;
	}
	#particles-js {
		position: fixed;
		top: 0px; left: 0px;
		z-index: -1;
		width: 100%;
		height: 100%;
	}
	body{
		background-image:  linear-gradient( rgba(0, 0, 0, 0.8), rgba(0, 0, 0, 0.8) ),  url("img/bg.png");
		color: #ffffff;
		z-index: -100;
	}

</style>

</head>
<body>

<?php 
	// Enter your API key
	$url = file_get_contents("https://api.thingspeak.com/channels/616351/feeds.json?api_key="-------"&results=2");
	$character = json_decode($url, true);
	$data = $character["feeds"][0];
	header("Refresh:1");
?>
<div class="page-header" style="font-family: 'Poor Story', cursive; text-align: center;">
	<h1 style="font-size: 50px; color:#ffffff;">Smart Parking System</h1>
</div>
<div class="container-fluid" align="center">
	<div id="particles-js"></div>
    <script src="particles.js"></script>
    <script src="app.js"></script>
	<div class="table-responsive" style="font-size: 20px;">
		<table class="table">
			<thead>
				<tr>
					<th> Position </th>
					<th> Availability </th>
				</tr>
			</thead>
		 	<?php for($j = 1; $j<5; $j++) {
		 	$field = 'field'.$j ?> 
				<tbody>
					<tr>
	 					<td><?php echo "Parking Spot ".$j; ?></td>
						<td> 
							<?php if ($data[$field] == 1) { ?>
								<p><span class="glyphicon glyphicon-ok green-icon"></span></p>
							<?php } else { ?>
								<p><span class="glyphicon glyphicon-remove red-icon"></span></p>
							<?php }?>
						</td>
		 			</tr>
				</tbody>
			<?php } ?>
		</table>
	</div>

</div>
</body>
</html>
