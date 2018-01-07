var f2 = function(b,d){
	//f2.js music staff
  var _v			= "v0.0.59";  

  var _ui = new _UIClass;
  function _jgClass(id){
	var _jg = new jsGraphics(id);
	this.upate = function(){
		_jg.clear();
		_jg.setColor("red");
		_jg.fillRect(0,0,100,100);
		_jg.paint();
	}   
  }
  function _UIClass(){   
	var _myWrap		= null;
    this.blrView	= function(b,d)
    { 
		if(_myWrap==null){		
			_myWrap = blo0.blMDiv(document.body,"id_div__myWrap","_myMsgWrap:" + _v,10,50,400,200,"brown");  
			_myWrap.divView = blo0.blDiv(_myWrap,_myWrap.id+"divView","divView",blGrey[0]);
			_myWrap.jg		= new _jgClass(_myWrap.divView.id);
			_myWrap.jg.upate();
		}
	  _on_off_div(b,_myWrap);
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
