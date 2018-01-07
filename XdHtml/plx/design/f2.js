var f2 = function(b,d){
	//f2.js music staff
  var _v			= "v0.0.49"; 
 

  var _ui = new _UIClass;
  function _UIClass(){  
    this.blrGetNewData	= function(b,d)
    { 
	  _w.blhSetView(d);
      blo0.blAjx(_w,url);
    }
    this.blrAboutMe = function(b,d){
	  var s = _v;
	  var LastSrcHref = "https://littleflute.github.io/vc6/XdHtml/plx/design/f2.js";
	  var UpdateHref = "https://github.com/littleflute/vc6/edit/master/XdHtml/plx/design/f2.js";
	  s += "<br>music staff<br>"; 
	  var style = "color:lightblue;";
	  var target = "_blank";
	  s += blo0.blhMakeLink(" f2.js ",LastSrcHref,style,target);
	  s += blo0.blhMakeLink(" f2.js* ",UpdateHref,style,target);
      d.innerHTML = s;  
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
