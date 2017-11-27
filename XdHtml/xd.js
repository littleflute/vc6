var QueryString = function () 
{
  var query_string = {};
  var query = window.location.search.substring(1);
  var vars = query.split("&");
  for (var i=0;i<vars.length;i++) {
    var pair = vars[i].split("=");
    if (typeof query_string[pair[0]] === "undefined") {
      query_string[pair[0]] = decodeURIComponent(pair[1]);
    } else if (typeof query_string[pair[0]] === "string") {
      var arr = [ query_string[pair[0]],decodeURIComponent(pair[1]) ];
      query_string[pair[0]] = arr;
    } else {
      query_string[pair[0]].push(decodeURIComponent(pair[1]));
    }
  } 
  return query_string;
}();

var refreshTimes = 0;
if(QueryString.r)
{
	refreshTimes = parseInt(QueryString.r) + 1;
}
else
{
	refreshTimes = 0;
}
    

//Media Build
function makemedia (strURL) {
	var strHtml;	
	strHtml ="<object id='MediaPlayer' width='400' height='64' classid='clsid:6bf52a52-394a-11d3-b153-00c04f79faa6'>";
    	strHtml+="<param name='url' value=\""+ strURL +"\">";
    	strHtml+="<param name='volume' value='100'>";
    	strHtml+="<param name='loop' value='true'>";
    	strHtml+="<param name='autoStart' value='0'>";
        strHtml+="</object>";        
	return strHtml;
}
function playmedia(strID,strURL) {
	strID.replace(" ","%20");
	var objDiv=document.getElementById(strID); 
		objDiv.innerHTML=makemedia(strURL);
}
var wrap = document.getElementById("xddbg");

function xdDbgMsg(str)
{
	if(wrap){
		var s = xddbg.innerHTML;
		s += str;
		s += "<br>";
		wrap.innerHTML =s;
	}
}

xdDbgMsg("xddbg: v0.0.21 refreshTimes="+refreshTimes); 
playmedia("idMedia","file:///C:/Users/13699/xd1/Mp3Player/blMp3Player-master/cd1/01.mp3");
if(blo0){
	if(wrap)
	{
		var nav = blo0.blDiv(wrap,"xdNav","xdNav");
		var l1 = blo0.blLink(nav,"l1","index.html","index.html?r="+refreshTimes,"Chartreuse");
		var l2 = blo0.blLink(nav,"l2","jsgraphics.html","jsgraphics.html","purple");
		var l3 = blo0.blLink(nav,"l3","1.html","1.html","white");
		var a = nav.getElementsByTagName('a');
		for(i in a)
		{
			a[i].onmouseover = function(){
				this.style.backgroundColor = "yellow";
			};
			a[i].onmouseout = function(){
				this.style.backgroundColor = "white";
			};
		}
	}
}