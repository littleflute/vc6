//picViewer.js

function _blPicViewerClass ()
{
	var srcBase = "https://raw.githubusercontent.com/littleflute/pro-javascript-design-patterns/master/cnbook/";
	var pageID = 0;

	var _curFileUrl = "";
	var _viewer = null;

	this.blrPicView = function(b,d){
		if(!d.v){
			d.v = blo0.blMDiv(d,d.id+"mdiv","blrPicView",110,110,500,400, blGrey[5]); 
			_viewer = d.v.d = blo0.blDiv(d.v,d.v.id+"d","d",blGrey[1]);  
			_viewer.innerHTML = '<div id = "dbg"></div>' + '<img id="xdImg" src="">';

		}
		_on_off_div(b,d.v);
	}
	this.blrF_Add_1 = function(b,d){
		if(_viewer){
			myFunction(1);
		} 
	}
	this.blrF_minor_1 = function(b,d){
		if(_viewer){
			myFunction(-1);
		} 
	}	 
	this.blrF_w_800 = function(b,d){
		if(_viewer){
			_viewer.style.width = "800px";
		} 
	}	 
	this.blrF_w_500 = function(b,d){
		if(_viewer){
			_viewer.style.width = "500px";
		} 
	}	 


	function xdNum2Str(n) {
		var s = "";
		if(n>=0 && n<=9)
		{
    		s = "000" + n.toString() + ".jpg";
		}
		else if(n>=10 && n<=99)
		{
    		s = "00" + n.toString() + ".jpg";
		}
		else if(n>=100 && n<=999)
		{
    		s = "0" + n.toString() + ".jpg";
		}
		return s;
	}

	function myFunction(nAdd) {
		var i = document.getElementById("xdImg");
		if(i)
		{
			pageID += nAdd;
    		var src = srcBase + xdNum2Str(pageID);
        
			var d = document.getElementById("dbg");
			d.innerHTML = src;
    		i.src = src;
		i.style.width = "100%";
		}
		else
		{
    		alert(i);
		}
	}

}
var d = bl$( "id_div_4__blPicViewerClass" );
var s = "blPicViewer_v0.0.11";
d.v = blo0.blMDiv(d,d.id+"mdiv",s,110,110,500,400, blGrey[3]); 
d.v.d = blo0.blDiv(d.v,d.v.id+"d","d",blGrey[1]); 
blo0.blShowObj2Div(d.v.d,new _blPicViewerClass);


