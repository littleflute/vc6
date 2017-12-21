var f3 = function(b,d){
	//f3.js  
	var _v = "v0.0.36";
	var _myView = null;

	blo0.blScript("id_script_book","https://littleflute.github.io/cchess0/cchess/book.js");
	blo0.blScript("id_script_position","https://littleflute.github.io/cchess0/cchess/position.js");
	blo0.blScript("id_script_search","https://littleflute.github.io/cchess0/cchess/search.js");
	blo0.blScript("id_script_board","https://littleflute.github.io/cchess0/cchess/board.js");
	blo0.blScript("id_script_cchess","https://littleflute.github.io/cchess0/cchess/cchess.js");
 
  var _ui = new _UIClass;
  function _UIClass(){  
	var _cchessBoard = null;
	var _myBoardWrap	= null;
	var _myMsgWrap	= null;
	var divMsg		= null;
    this.blrMsg	= function(b,d)
    { 
		if(_myMsgWrap==null){		
			_myMsgWrap = blo0.blMDiv(document.body,"id_div__myMsgWrap","_myMsgWrap:" + _v,50,50,400,200,"green");  
			divMsg = blo0.blDiv(_myMsgWrap,_myMsgWrap.id+"divMsg","divMsg",blGrey[0]);
		}
	  _on_off_div(b,_myMsgWrap);
    }
    this.blrBoard = function(b,d){ 
		if(_myBoardWrap==null){		
			_myBoardWrap = blo0.blMDiv(document.body,"id_div___myBoardWrap","_myBoard:" + _v,550,50,400,200,"brown"); 
			var divBoard = blo0.blDiv(_myBoardWrap,_myBoardWrap.id+"_divBoard","",blGrey[0]);
			var imgPath = "https://littleflute.github.io/cchess0/cchess/images/";
			var soundsPath = "https://littleflute.github.io/cchess0/cchess/sounds/";	
			_cchessBoard = new Board(divBoard,imgPath , soundsPath);
			_cchessBoard.clickSquare = _newClick;
		}
	  _on_off_div(b,_myBoardWrap);
    };
    this.blrA0A1	= function(b,d)
    {   
                go(_cchessBoard,'a','0','a','1');
    }
    this.blrB7E7	= function(b,d)
    {   
                go(_cchessBoard,'b','7','e','7');
    }
    this.blrAboutMe = function(b,d){
	  var s = _v;
	  s += "<br>Chinese chess board<br>"; 
      d.innerHTML = s;
	  var LastSrcHref = "https://littleflute.github.io/vc6/XdHtml/plx/design/f3.js";
	  var l = blo0.blLink(d,d.id+"LastSrcHref","LastSrcHref",LastSrcHref,"blue");
	  var UpdateHref = "https://github.com/littleflute/vc6/edit/master/XdHtml/plx/design/f3.js";
	  var l = blo0.blLink(d,d.id+"UpdateHref","UpdateHref",UpdateHref,"Salmon");
	  _on_off_div(b,d);
    };
	var go = function(board,c1,c2,c3,c4){ 
		if(board==null) return;
        			var g1 = x[c2]+getY(c1); 
        			var g2 = x[c4]+getY(c3); 
                    var g1 = board.flipped(g1);
                    var g2 = board.flipped(g2); 
            		board.imgSquares[g1].onmousedown(); 
            		board.imgSquares[g2].onmousedown(); 
    			}
	var getY = function(c)
    			{
                	if(c=='a') return 0;
                    if(c=='b') return 1;
                    if(c=='c') return 2;
                    if(c=='d') return 3;
                    if(c=='e') return 4;
                    if(c=='f') return 5;
                    if(c=='g') return 6;
                    if(c=='h') return 7;
                    if(c=='i') return 8;
                }
    var x = [195,179,163,147,131,115,99,83,67,51];

	function _newClick(sq_) { 
					function myA_I (c){ 
                					if(c==3) return "a";
									if(c==4) return "b";
									if(c==5) return "c";
									if(c==6) return "d";
									if(c==7) return "e";
									if(c==8) return "f";
									if(c==9) return "g";
									if(c==10) return "h";
									if(c==11) return "i";
								  }
					function my0_9 (c){ 
                					if(c==3) return 9;
									if(c==4) return 8;
									if(c==5) return 7;
									if(c==6) return 6;
									if(c==7) return 5;
									if(c==8) return 4;
									if(c==9) return 3;
									if(c==10) return 2;
									if(c==11) return 1;
									if(c==12) return 0;
								  }
  					var sq = this.flipped(sq_);
					var s = "sq_:" + sq_;
					s += "sq:" + sq;
					s += "xy:" + myA_I(sq & 15);
					s +=  my0_9(sq >> 4);
    
					divMsg.innerHTML = s;
    
    
				  if (this.busy || this.result != RESULT_UNKNOWN) {
					return;
				  }
				  var pc = this.pos.squares[sq];
				  if ((pc & SIDE_TAG(this.pos.sdPlayer)) != 0) {
					this.playSound("click");
					if (this.mvLast != 0) {
					  this.drawSquare(SRC(this.mvLast), false);
					  this.drawSquare(DST(this.mvLast), false);
					}
					if (this.sqSelected) {
					  this.drawSquare(this.sqSelected, false);
					}
					this.drawSquare(sq, true);
					this.sqSelected = sq;
				  } else if (this.sqSelected > 0) {
					this.addMove(MOVE(this.sqSelected, sq), false);
				  }
				}
  }
   
  var _myUI = function(b,d){ 
      var _myView	= blo0.blDiv(d,d.id + "_myView","_myView",blGrey[5]);
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
	ta.f3 = f3;
	ta.value = ta.f3;
}
