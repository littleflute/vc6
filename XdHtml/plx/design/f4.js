var f4 = function(b,d){
  //f4.js Timer
  var _v = "v0.0.37";
  var _myUI = function(b,d){ 
      var _myView	= blo0.blDiv(d,d.id + "_myView","_myView",blGrey[5]);
	  if(!_myView.blFirst){
		var _ui = new _UIClass;
		blo0.blShowObj2Div(_myView,_ui);
		_myView.blFirst = true;
	  }
	  _on_off_div(b,d);
  };
  _myUI(b,d);

  function _UIClass(){   
	this.blrTimer = function(b,d){
	  var _myView	= blo0.blDiv(d,d.id + "_myView","_myView",blGrey[6]);
	  var _toolBar	= blo0.blDiv(d,d.id + "_toolBar","_toolBar",blGrey[5]);
	  if(!_myView.blFirst){
		var _timer = new _TimerClass(_myView);
		blo0.blShowObj2Div(_toolBar,_timer);
		_myView.blFirst = true;
	  }
	  _on_off_div(b,d);
	}; 
	this.bll1 = "---";
	this.blrAboutMe = function(b,d){
	  var s = _v;
	  s += "<br>timer<br>"; 
      d.innerHTML = s;
	  var LastSrcHref = "https://littleflute.github.io/vc6/XdHtml/plx/design/f4.js";
	  var l = blo0.blLink(d,d.id+"LastSrcHref","LastSrcHref",LastSrcHref,"blue");
	  var UpdateHref = "https://github.com/littleflute/vc6/edit/master/XdHtml/plx/design/f4.js";
	  var l = blo0.blLink(d,d.id+"UpdateHref","UpdateHref",UpdateHref,"Salmon");
	  _on_off_div(b,d);
    };

  }
  function _TimerClass(v){ 
    var _view	= v; 
	var ds		= [];
		var seconds = 1000;
		var minutes = 1000 * 60;
		var hours = minutes * 60;
		var days = hours * 24;
		var years = days * 365;

	var _sec = function(n){
		if(ds.length<n) {
			_view.innerHTML = ds.length;
			return;
		}
		var d = ds[n-1];
		var t = d.getTime();

		var s = Math.round(t / seconds);
		_view.innerHTML = s;
	};

	this.blrBPM_10 = function(b,d){
		if(!d.nTimes)
		{
			d.nTimes = 1;
			d.t0		= (new Date).getTime();
			d.innerHTML = d.nTimes;
		}
		else if (d.nTimes==1){
			d.nTimes++;
			d.t1		= (new Date).getTime();
			var dt		= d.t1 - d.t0;
			var bpm		= 60 * 1000 * 10/dt;
			d.innerHTML = "bpm= " + bpm;
		}
		else if (d.nTimes==2){
			d.nTimes = 1;
			d.t0		= (new Date).getTime();
			d.innerHTML = d.nTimes;
		}
	};

	this.blrD2 = function(b,d){
		_sec(2);
	};
	this.blrGetDate = function(b,d){
		ds.push(new Date);
		if(ds.length>1){
			var t = ds[ds.length-1].getTime() - ds[0].getTime();
			var beats = ds.length-1; 
			var bmp = 60*1000 * beats/t;
			_view.innerHTML = "bpm: " + bmp;
		}
		blo0.blShowObj2Div(d,ds);
	};
  }
};

var ta = bl$( "id_ta_4_NewClass" );
if( ta ){
	ta.f4 = f4;
	ta.value = ta.f4;
}
