function update() {
	var xmlhttp = new XMLHttpRequest();
	var query = '';
	
	xmlhttp.onreadystatechange = function() {
		if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
			var status = JSON.parse(xmlhttp.responseText);
			if (shouldAddControls) {
				shouldAddControls = false;
				addControls(status);
			}
				
			for (i = 0; i < numTrainLines; i++) {
				document.getElementById('speed[' + i + ']').value = status['speed'][i];
				document.getElementById('speed_val[' + i + ']').value = status['speed'][i] + '%';
			}
			controlValues = status['speed'];
		}
	}
	
	if (controlsHaveChanged()) {
		for (i = 0; i < numTrainLines; i++) {
			if (query.length > 0) { query = query + '&'; }
			query = query + 'speed[' + i + ']=' + document.getElementById('speed[' + i + ']').value;
		}
	}

	xmlhttp.open('GET', '/api?' + query, true);
	xmlhttp.send();
}

window.setInterval(update, 500);
