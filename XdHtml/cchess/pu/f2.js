var f2 = function(b,d){
	//f2.js 
  var _v			= "v0.0.40";
  var url			= "http://www.xqbase.com/xqbase/?gameid=2419"; 
 

  var _w = new _ajxWorkerClass;
  function _ajxWorkerClass(){ 
    var _myView = null;
    this._2do	= function(txt)
    {
		_myView.innerHTML = txt;
    } 
    this._error	= function(txt)
    {
		_myView.innerHTML = txt;
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
	ta.f2 = f2;
	ta.value = ta.f2;
}
