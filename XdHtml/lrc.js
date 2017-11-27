var QueryString = function () 
{
  // This function is anonymous, is executed immediately and 
  // the return value is assigned to QueryString!

  var query_string = {};

  var query = window.location.search.substring(1);

  var vars = query.split("&");

  for (var i=0;i<vars.length;i++) {

    var pair = vars[i].split("=");

        // If first entry with this name

    if (typeof query_string[pair[0]] === "undefined") {

      query_string[pair[0]] = decodeURIComponent(pair[1]);

        // If second entry with this name

    } else if (typeof query_string[pair[0]] === "string") {

      var arr = [ query_string[pair[0]],decodeURIComponent(pair[1]) ];

      query_string[pair[0]] = arr;

        // If third or later entry with this name

    } else {

      query_string[pair[0]].push(decodeURIComponent(pair[1]));

    }

  }
 
  return query_string;

}();
//QueryString.l


function _blVMPlayer()
{
	var nTime = 0; 
	var _myFun = function(_this){
		return function(){
			nTime += 0.01;
		}
	}(this);

	this.blrPlay = function()
	{
		setInterval(_myFun,10);
	}
	this.blrGetCP = function()
	{
		return nTime;
	}
}

var lrcTimer0;
var lrcTimer1;
var xdMin;
  function _golrcolor(t)
  { 
    if(t<=10)
      lrcTimer1 = setTimeout("_golrcolor("+t+")",xdMin*10);
  }
  function _golrcoll(s)
  { 
		lrcoll.style.top = -(s++)*2;
		if(s<=9)
			lrcTimer0 = setTimeout("_golrcoll("+s+")",xdMin*10);
  }
 
lrcobj = new blLrcClass(lrcdata.innerHTML);

function blLrcClass(tt)
{	
	var xdType = 4; //5 - html5; 4 - vc6; 3 - No Real Player;
	if (QueryString.l==undefined) xdType = 3;
	
	if (QueryString.l==5) xdType = 5;
	if (QueryString.l==4) xdType = 4;
	if (QueryString.l==3) xdType = 3;
	var o = new blClass;
	var blVMP = new _blVMPlayer;
	function _makeMPObj (strURL) {
		var strHtml;	
		strHtml ="<object id='idLyricMP' width='400' height='64' classid='clsid:6bf52a52-394a-11d3-b153-00c04f79faa6'>";
    	strHtml+="<param name='url' value=\""+ strURL +"\">";
    	strHtml+="<param name='volume' value='10'>";
    	strHtml+="<param name='loop' value='true'>";
    	strHtml+="<param name='autoStart' value='0'>";
		strHtml+="</object>";     
		return strHtml;
	}	

	function _InitPlayer(t,oDivBoss,strURL) { 
		switch(t)
		{
		case 3:
			oDivBoss.innerHTML = "No Real Player v0.0.11";
			blVMP.blrPlay();
			break;
		case 4:
			oDivBoss.innerHTML = _makeMPObj(strURL);
			break;
		case 5:
			o.blAudio(oDivBoss,"idLyricMP",strURL); 
			var playerObj = document.getElementById("idLyricMP");
			playerObj.volume = .1;
			break;
		} 

	}
  var nMyTimer = 0;
  this.TimerFun = function(_this)
  {
		return function(){ 
			var d = document.getElementById("idMyTimer");
			var s = "";//d.innerHTML;
			nMyTimer++;
			s += nMyTimer;
			var playerObj = document.getElementById("idLyricMP");
			s += " QueryString.l = " + QueryString.l;
			s += " blVMP.blrGetCP = " + blVMP.blrGetCP();
			s += "idMovingLyr.style.top = " + idMovingLyr.style.top;
			s += "<br>";
			d.innerHTML = s;
			_this.xdRun(playerObj);
		}
  }(this);
 

  var _CreateLyrBoard2 = function(oBoss)
  {	
		var d2Title = o.blDiv(oBoss,"d2Title","d2Title: v0.0.2","blue");
		var d2Body = o.blDiv(oBoss,"d2Body","d2Body: v0.0.13","DarkOrchid");
		var d2BodyContend = o.blDiv(oBoss,"d2BodyContend","d2BodyContend: V x.x.x","DarkSeaGreen");

 

		var s = "";
		s += '<div id="lrcollbox" style="overflow:hidden; height:260; width:460; background-color:#59a;">'; 
		s += '<table border="1" cellspacing="0" cellpadding="0" width="100%" id="lrcoll"';
		s += ' style="position:relative; top: -20px;" oncontextmenu="return false;">';
		s += '<tr><td nowrap height="20" align="center" id="lrcwt1"></td></tr>';
		s += '<tr><td nowrap height="20" align="center" id="lrcwt2"></td></tr>';
		s += '<tr><td nowrap height="20" align="center" id="lrcwt3"></td></tr>';
		s += '<tr><td nowrap height="20" align="center" id="lrcwt4"></td></tr>';
		s += '<tr><td nowrap height="20" align="center" id="lrcwt5"></td></tr>';
		s += '<tr style="color:#BDB76B;">';
			s += '<td nowrap height="20" align="center" id="lrcwt6">';
				s += '</td></tr>'; 

		s += '<tr style="color:#BDB76B;">';
			s += '<td nowrap height="20" align="center">';
					s += '<div id="lrcwt7" style="overflow:hidden;position:relative; width:100%; color:#FFFF33; height:20">lrcwt7 ...</div>';
					s += '<div id="lrcfilter" style="overflow:hidden;position:relative;top: -20px; width:100%; color:#FFFF33; height:20">lrcfilter ...</div>';
				s += '</td></tr>'; 

		s += '<tr style="color:#BDB76B;">';
			s += '<td nowrap height="20">';
					s += '<div id="xdwrap">';
					s += '<div id="lrcbox" style="overflow:hidden;position:relative; width:100%; color:#800000; height:20">歌词加载中 ...</div>';
					s += '<div id="idMovingLyr" style="overflow:hidden;position:relative;top: -20px; width:0; color:#FFFF33; height:20">歌词加载中 ...</div>';
					s += '</div>';
				s += '</td></tr>'; 
 
		s += '<tr style="position:relative; top: -20px;color:#FF9900;"><!-- next to come words-->';
			s += '<td nowrap height="20" align="center" id="lrcwt8"></td>';
		s += '</tr>';
		s += '<tr style="position:relative; top: -20px;"><td nowrap height="20" align="center" id="lrcwt9"></td></tr>';
		s += '<tr style="position:relative; top: -20px;"><td nowrap height="20" align="center" id="lrcwt10"></td></tr>';
		s += '<tr style="position:relative; top: -20px;"><td nowrap height="20" align="center" id="lrcwt11"></td></tr>';
		s += '<tr style="position:relative; top: -20px;"><td nowrap height="20" align="center" id="lrcwt12"></td></tr>';
		s += '<tr style="position:relative; top: -20px;"><td nowrap height="20" align="center" id="lrcwt13"></td></tr>';
		s += '</table>';
		s += '</div>';
		
		d2BodyContend.innerHTML = s;
  } 
  var _CreateUI = function()
  {
	var xdVer	= "v1.0.26";
	var xdPlayerDiv = o.blDiv(document.body,"xdPlayerDiv","xdPlayerDiv");	 
	var divMP = o.blDiv(xdPlayerDiv,"mp1","xdxdxd","red"); 
	_InitPlayer(xdType,divMP,"file:///C:/Users/13699/xd/vc6/files/u0102.mp3"); 
	var xddbgDiv = o.blDiv(document.body,"xddbgLyric",xdVer,"green");
	var MyTimer = o.blDiv(document.body,"idMyTimer","idMyTimer");

	var od = o.blDiv(document.body,"oShowDiv","showDiv");
	//o.blShowObj2Div(od,lrcobj);	
	_CreateLyrBoard2(od);
  }
  
  _CreateUI();

  this.inr = [];
  this.min = [];
  this.oTime = 0;
  this.dts = -1;
  this.dte = -1;
  this.dlt = -1;
  this.ddh;
  this.fjh;
  idMovingLyr.style.width = 0;
  if(/\[offset\:(\-?\d+)\]/i.test(tt))
    this.oTime = RegExp.$1/1000;

  tt = tt.replace(/\[\:\][^$\n]*(\n|$)/g,"$1");
  tt = tt.replace(/\[[^\[\]\:]*\]/g,"");
  tt = tt.replace(/\[[^\[\]]*[^\[\]\d]+[^\[\]]*\:[^\[\]]*\]/g,"");
  tt = tt.replace(/\[[^\[\]]*\:[^\[\]]*[^\[\]\d\.]+[^\[\]]*\]/g,"");
  tt = tt.replace(/<[^<>]*[^<>\d]+[^<>]*\:[^<>]*>/g,"");
  tt = tt.replace(/<[^<>]*\:[^<>]*[^<>\d\.]+[^<>]*>/g,"");


  while(/\[[^\[\]]+\:[^\[\]]+\]/.test(tt))
  {
    tt = tt.replace(/((\[[^\[\]]+\:[^\[\]]+\])+[^\[\r\n]*)[^\[]*/,"\n");
    var zzzt = RegExp.$1;
    /^(.+\])([^\]]*)$/.exec(zzzt);
    var ltxt = RegExp.$2;
    var eft = RegExp.$1.slice(1,-1).split("][");
    for(var ii=0; ii<eft.length; ii++)
    {
      var sf = eft[ii].split(":");
      var tse = parseInt(sf[0],10) * 60 + parseFloat(sf[1]);
      var sso = { t:[] , w:[] , n:ltxt }
      sso.t[0] = tse-this.oTime;
      this.inr[this.inr.length] = sso;
    }
  }

  this.inr = this.inr.sort( function(a,b){return a.t[0]-b.t[0];} ); 

  for(var ii=0; ii<this.inr.length; ii++)
  {
    while(/<[^<>]+\:[^<>]+>/.test(this.inr[ii].n))
    {
      this.inr[ii].n = this.inr[ii].n.replace(/<(\d+)\:([\d\.]+)>/,"%=%");
      var tse = parseInt(RegExp.$1,10) * 60 + parseFloat(RegExp.$2);
      this.inr[ii].t[this.inr[ii].t.length] = tse-this.oTime;
    }

    idMovingLyr.innerHTML = "<font>"+ this.inr[ii].n.replace(/&/g,"&").replace(/</g,"<").replace(/>/g,">").replace(/%=%/g,"</font><font>") +"</font>";
 
    var fall = idMovingLyr.getElementsByTagName("font");
    for(var wi=0; wi<fall.length; wi++)
      this.inr[ii].w[this.inr[ii].w.length] = fall[wi].offsetWidth;
  //  this.inr[ii].n = "xddbg1a: " ;//idMovingLyr.innerText; //#xdm 1
  }


  for(var ii=0; ii<this.inr.length-1; ii++)
    this.min[ii] = Math.floor((this.inr[ii+1].t[0]-this.inr[ii].t[0])*10);

  this.min.sort(function(a,b){return a-b});
  xdMin = this.min[0]/2;

  var nXdDbgNum = 0;
  this.xdRun = function(xdMP)
  { 
	nXdDbgNum++;
	var xdCP;
	switch(xdType)
	{
	case 3: 
		xdCP = blVMP.blrGetCP(); 
		
		break;
	case 4:
		xdCP = xdMP.controls.currentPosition;  
		break;
	case 5:
		xdCP = xdMP.currentTime;  
		break;
	} 

    if(xdCP<this.dts || xdCP>=this.dte)
    {	
      var ii;
      for(ii=this.inr.length-1; ii>=0 && this.inr[ii].t[0]>xdCP; ii--){}
      if(ii<0) 
	  { 
			return;
	  }
 
      this.ddh = this.inr[ii].t;
      this.fjh = this.inr[ii].w;
      this.dts = this.inr[ii].t[0];
      this.dte = (ii<this.inr.length-1)?this.inr[ii+1].t[0]:xdCP;

      lrcwt1.innerText = this.retxt(ii-7);
      lrcwt2.innerText = this.retxt(ii-6);
      lrcwt3.innerText = this.retxt(ii-5);
      lrcwt4.innerText = this.retxt(ii-4);
      lrcwt5.innerText = this.retxt(ii-3);
      lrcwt6.innerText = this.retxt(ii-2);
  
      lrcwt7.innerText			= this.retxt(ii-1);
      lrcfilter.innerText		= this.retxt(ii-1);

      lrcwt8.innerText		= ">>>-"  + this.retxt(ii+1);
      lrcwt9.innerText		= this.retxt(ii+2);
      lrcwt10.innerText = this.retxt(ii+3);
      lrcwt11.innerText = this.retxt(ii+4);
      lrcwt12.innerText = this.retxt(ii+5);
      lrcwt13.innerText = this.retxt(ii+6);
      this.blSetTxt(this.retxt(ii)); 

      if(this.dlt==ii-1)
      {
        clearTimeout(lrcTimer0);
        if(lrcoll.style.pixelTop!=0) lrcoll.style.top = 0;
  
		_golrcoll(0);  
        clearTimeout(lrcTimer1);  
        _golrcolor(0); 
      }
      else if(parseInt(lrcoll.style.top)!=-20)
      {
	    clearTimeout(lrcTimer0);
        lrcoll.style.top = -20;
        clearTimeout(lrcTimer1);
      }

      this.dlt = ii; 
    }

    var bbw = 0;
    var ki;
    for(ki=0; ki<this.ddh.length && this.ddh[ki]<=xdCP; ki++)
      bbw += this.fjh[ki];
    var kt = ki-1;
    var sc = ((ki<this.ddh.length)?this.ddh[ki]:this.dte) - this.ddh[kt];
    var tc = xdCP - this.ddh[kt];
    bbw -= this.fjh[kt] - tc / sc * this.fjh[kt];
    if(bbw>lrcbox.offsetWidth)
      bbw = lrcbox.offsetWidth;
    idMovingLyr.style.width = Math.round(bbw);
  }

  this.retxt = function(i)
  {
    return (i<0 || i>=this.inr.length)?"xxxxxxxx":this.inr[i].n;
  }

  this.blSetTxt = function(txt)
  {
    lrcbox.innerText		= txt;
    idMovingLyr.innerText	= txt;
  }
  
  this.blSetTxt("系统暂没有相关歌词...");
  lrcwt1.innerText = "111111111111111111";
  lrcwt2.innerText = "";
  lrcwt3.innerText = "";
  lrcwt4.innerText = "";
  lrcwt5.innerText = "";
  lrcwt6.innerText = ""; 
  lrcwt7.innerText = "";
  lrcfilter.innerText = "xxxxxxxxxxxxxxxxxxxxxxxx";
  lrcwt8.innerText = "";
  lrcwt9.innerText = "";
  lrcwt10.innerText = "";
  lrcwt11.innerText = "";
  lrcwt12.innerText = "";
  lrcwt13.innerText = "";
	 
  this.blRun = function(_this)
  {
		return function(_this){
			setInterval(_this.TimerFun,10);
		}
  }(this); 
}//END: blLrcClass


lrcobj.blRun(lrcobj);

