// blEBooks.js
// blEBooks.js*:	https://github.com/littleflute/vc6/edit/master/XdHtml/plx/blEBooks.js
// blEBooks.js:	https://littleflute.github.io/vc6/XdHtml/plx/blEBooks.js


function _blEBooksClass ()
{
	var _wrap = bl$( "id_div_4_blEBooksClass" );

	this.v = "_blEBooksClass v0.0.5";
	this.blrBook1 = function(b,d){
		_wrap.update("https://raw.githubusercontent.com/littleflute/pro-javascript-design-patterns/master/cnbook/");
	}

}
var d = bl$( "id_div_4_blEBooksClass" );
var s = "blEBooks_v0.0.22 - ";
s += "<a target = '_blank' href='https://littleflute.github.io/vc6/XdHtml/plx/blEBooks.js'>blEBooks.js</a> - ";
s += "<a target = '_blank' href='https://github.com/littleflute/vc6/edit/master/XdHtml/plx/blEBooks.js'>blEBooks.js*</a>";

d.v = blo0.blDiv(d,d.id+"div",s,blGrey[3]); 
d.v.d = blo0.blDiv(d.v,d.v.id+"d","d",blGrey[1]); 
blo0.blShowObj2Div(d.v.d,new _blEBooksClass);


