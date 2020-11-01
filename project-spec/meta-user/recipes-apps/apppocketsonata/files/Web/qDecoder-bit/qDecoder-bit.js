//--------------------------------------------------------------
//-- The qDecoder Project             http://www.qDecoder.org --
//--                                                          --
//--           Copyright (C) 2007 Seung-young Kim             --
//--------------------------------------------------------------

//
// User Define Variables
//
var Q_BIT_DIALOGUE_WIDTH="380";
var Q_BIT_DIALOGUE_HEIGHT="140";

var Q_BIT_DRAWRATE="1000";	// set drawing interval (how often the server checks the status)
var Q_BIT_TEMPLATE="../qDecoder-bit/qDecoder-bit.html";	// set progress template

//
// DO NOT MODIFY BELOW UNTIL YOU UNDERSTAND WHAT IT DOES EXACTLY
//

function qBit(qForm) {
	
	// check field
	if(!eval(qForm.Q_BIT_ID)) {
		alert("Q_BIT_ID must be defined.");
		return false;
	}

	var q_upload_action = qForm.action;
    
    var q_bit_id = (new Date()).getTime() % 1000000000;
    qForm.Q_BIT_ID.value = q_bit_id;

	// check browser
	var qBrowserVersion = navigator.appVersion;
	winstyle = "dialogWidth="+Q_BIT_DIALOGUE_WIDTH+"px; dialogHeight:"+Q_BIT_DIALOGUE_HEIGHT+"px; center:yes; help:no; scroll:no; status:no;";

	if (qBrowserVersion.indexOf('MSIE') != -1 && qBrowserVersion.substr(qBrowserVersion.indexOf('MSIE')+5,1) > 4) {
		window.showModelessDialog(q_upload_action+"?Q_BIT_ID="+q_bit_id+"&Q_BIT_DRAWRATE="+Q_BIT_DRAWRATE+"&Q_BIT_TEMPLATE="+Q_BIT_TEMPLATE, null, winstyle);
	} else {
		window.open(q_upload_action+"?Q_BIT_ID="+q_bit_id+"&Q_BIT_DRAWRATE="+Q_BIT_DRAWRATE+"&Q_BIT_TEMPLATE="+Q_BIT_TEMPLATE, null, "width=680,height=710,status=no,toolbar=no,menubar=no,location=no,resizable=no,scrollbars=no,copyhistory=no");
	}	

	return true;
}
