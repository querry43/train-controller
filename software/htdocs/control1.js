var controlValues = [];
var numTrainLines = 0;
var shouldAddControls = true;

function addControls(status) {
	numTrainLines = status['num_train_lines'];
	var container = document.getElementById('control_container');
	for (i = 0; i < numTrainLines; i++) {
		container.innerHTML = container.innerHTML
		+ 'Line ' + (i+1) + '<br />'
		+ '<output id="speed_val[' + i + ']" for="speed[' + i + ']"></output><br />'
		+ '<input type="range" id="speed[' + i + ']" min="-100" max="100" step="10" style="width: 50%;"><br />'
		+ '<br />';
		controlValues = status['speed'];
	}
}

function controlsHaveChanged() {
	for (i = 0; i < numTrainLines; i++) {
		if (document.getElementById('speed[' + i + ']').value != controlValues[i]) {
			return true;
		}
	}
	return false;
}
