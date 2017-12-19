var f0 = function(b,d){
  //f0.js * xau update data
  var _v			= "v0.0.38";
  var url			= "http://api.baidao.com/api/hq/npdata.do?ids=201"; 
 

  var _w = new _ajxWorkerClass;
  function _ajxWorkerClass(){ 
    var _myView = null;
    this._2do	= function(txt)
    {
		_myView.innerHTML = txt;
		var s = "var o = " + txt;
		eval(s);
		blo0.blShowObj2Div(_myView,o[0]);
    } 
    this.blhSetView	= function(d)
    {
		_myView = d;
    } 
  }
  var _ui = new _UIClass;
  function _UIClass(){  
    this.blrGetNewData	= function(b,d)
    { 
	  _w.blhSetView(d);
      blo0.blAjx(_w,url);
    }
    this.blrAboutMe = function(b,d){
	  var s = _v;
	  s += "<br>xau update data<br>";
	  s += url; 
      d.innerHTML = s;
	  var LastSrcHref = "https://littleflute.github.io/vc6/XdHtml/plx/design/f0.js";
	  var l = blo0.blLink(d,d.id+"LastSrcHref","LastSrcHref",LastSrcHref,"blue");
	  var UpdateHref = "https://github.com/littleflute/vc6/edit/master/XdHtml/plx/design/f0.js";
	  var l = blo0.blLink(d,d.id+"UpdateHref","UpdateHref",UpdateHref,"Salmon");
	  _on_off_div(b,d);
    };
  }
   
  var _myUI = function(b,d){ 
      _myView	= blo0.blDiv(d,d.id + "_myView","_myView",blGrey[5]);
	  if(!_myView.blFirst){
		blo0.blShowObj2Div(_myView,_ui);
		_myView.blFirst = true;
	  }
	  _on_off_div(b,d);
  };
  _myUI(b,d);
 
};

var ta = bl$( "id_ta_4_NewClass" );
if( ta ){
	ta.f0 = f0;
	ta.value = ta.f0;
}
