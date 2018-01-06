var f2 = function(b,d){
	//f2.js music staff
  var _v			= "v0.0.48"; 
 

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
	  s += "<br>music staff<br>";
	  s += "<a href='";
	  s += LastSrcHref;
	  s += "' ";
	  s += " style='color:gold;' ";
	  s += " target='_blank' ";
	  s +=">LastsrcHref"; 
	  s += "</a>";
	  var href = "https://littleflute.github.io/vc6/XdHtml/plx/design/f2.js";
	  var style = "color:lightblue;";
	  var target = "_blank";
	  s += blo0.blhMakeLink(" f2.js ",href,style,target);
      d.innerHTML = s; 
	  var UpdateHref = "https://github.com/littleflute/vc6/edit/master/XdHtml/plx/design/f2.js";
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
