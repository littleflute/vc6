var ls = [
	"xd1",	"xd2",	"xd3",	"xd4",	"xd5",
	"xd6", "xd7","xd8","xd9",
];
var ld = bl$("id_div_xd_pu_list");

if(ld){
	var html = "";
	html += "<a target='_blank' href='";
	html += "https://github.com/littleflute/vc6/edit/master/XdHtml/cchess/pu/xdPuList.js";
	html += "'>";
	html += "v0.0.61";
	html += "</a>";
	html += "<a target='_blank' href='";
	html += "pu/xdPuList.js";
	html += "' style='color:brown;'>";
	html += "src";
	html += "</a>";
	ld.innerHTML = html;
	var lv = blo0.blDiv(ld,ld.id+"_lv_","lv",blGrey[5]);
	var div4TA = blo0.blDiv(ld,ld.id+"div4TA","div4TA",blGrey[1]);
	var divToolBar = blo0.blDiv(ld,ld.id+"divToolBar","divToolBar",blGrey[5]);
	var ta = blo0.blTextarea(div4TA,"id_ta_4_puList","pu",blGrey[3]);
	ta.style.width = "100%";
	ta.style.height = "200px";
	for(i in ls){
		var b = blo0.blBtn(ld,ld.id+"_btn_"+i,ls[i],blGrey[0]);
		b.onclick = function(_fileName){
			return function(){
				var idScript = "id_script_" + _fileName; 
				if(bl$(idScript)){
					var ta = bl$( "id_ta_4_puList" );
					var s = "ta.value = ta." + _fileName;
					eval(s);
				}
				else{
					s = "pu/" + _fileName + ".js";
					lv.innerHTML = s;

					blo0.blScript(idScript,s);
				}
			}
		}(ls[i]);
		var url = "https://github.com/littleflute/vc6/edit/master/XdHtml/cchess/pu/";
		url += ls[i] + ".js";
		var l = blo0.blLink(ld,ld.id+"UpdateHref"+i,"u*",url,"Salmon");

	} 
	var l = blo0.blLink(ld,ld.id+"new","new+","https://github.com/littleflute/vc6/new/master/XdHtml/cchess/pu","Salmon");

	var btnParsePu = blo0.blBtn(divToolBar,divToolBar.id+"btnParsePu","btnParsePu",blGrey[0]);
	btnParsePu.onclick = function(n_){
		var ta = bl$( "id_ta_4_puList");		
		var txt = "var f = " + ta.value; 
		eval(txt);
		var s = f();
		var a = s.split("+");
		for(i in a){
			var b = blo0.blBtn(divToolBar,divToolBar.id+"_pu_btn_"+i,a[i],blGrey[0]);
			b.onclick = function(_btn){
				return function(){ 
				    var t = _btn.innerHTML;
					var a = t.charAt(0);
					var l1 = a.toLowerCase(); 
					var a = t.charAt(1);
					var l2 = a.toLowerCase(); 
					var a = t.charAt(3);
					var l3 = a.toLowerCase(); 
					var a = t.charAt(4);
					var l4 = a.toLowerCase();  
					ld.board.blhGo(ld.board,l1,l2,l3,l4);
					_btn.style.backgroundColor = "gold";
				}
			}(b);
			
		}
	};
}
