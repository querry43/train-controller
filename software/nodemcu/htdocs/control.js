var numTrainLines = 0;
var shouldAddControls = true;
var xmlhttp = new XMLHttpRequest();
var controlsHaveChanged = false;
var postChange = false;

function control(i) {
  return 'Line ' + (i+1) + '<br />'
    + '<output id="speed_val[' + i + ']" for="speed[' + i + ']"></output><br />'
    + '<input type="range" id="speed[' + i + ']" min="-100" max="100" step="10" style="width: 50%;" oninput="controlChange()"><br />'
    + '^<br />'
    + '<br />';
}

function controlChange() { controlsHaveChanged = true; }

function addControls(status) {
  numTrainLines = status['num_train_lines'];
  var container = document.getElementById('control_container');
  for (i = 0; i < numTrainLines; i++) {
    container.innerHTML = container.innerHTML + control(i);
  }
}

function updateControls(status) {
  for (i = 0; i < numTrainLines; i++) {
		var speedElement = document.getElementById('speed[' + i + ']');
		speedElement.oninput = null;
    speedElement.value = status['speed'][i];
		speedElement.oninput = controlChange;
    document.getElementById('speed_val[' + i + ']').value = status['speed'][i] + '%';
  }
}

function queryString() {
	if (controlsHaveChanged) {
		var query = '?'
		for (i = 0; i < numTrainLines; i++) {
			if (query.length > 0) { query = query + '&'; }
			var speed = document.getElementById('speed[' + i + ']').value;
			query = query + 'speed.' + i + '=' + speed;
		}
		return query;
	} else {
		return '';
	}
}

function refresh() {
  var query = queryString();
	if (controlsHaveChanged) {
		controlsHaveChanged = false;
		postChange = true;
	}
  xmlhttp.open('GET', '/api' + query, true);
  xmlhttp.send();
}

xmlhttp.onreadystatechange = function() {
  if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
    var status = JSON.parse(xmlhttp.responseText);
    if (shouldAddControls) {
      shouldAddControls = false;
      addControls(status);
    }
		
		if (!controlsHaveChanged) {
			updateControls(status);
		}
		
		postChange = false;
		
		window.setTimeout(refresh, 100);
  }
}

refresh();
