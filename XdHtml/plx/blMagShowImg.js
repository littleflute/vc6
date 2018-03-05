// blMagShowImg.js
// blMagShowImg.js*:	https://github.com/littleflute/vc6/edit/master/XdHtml/plx/blMagShowImg.js
// blMagShowImg.js:		https://littleflute.github.io/vc6/XdHtml/plx/blMagShowImg.js


function getEventObject(W3CEvent) {//事件标准化函数
 return W3CEvent || window.event;
}
function getPointerPosition(e) {//兼容浏览器的鼠标x,y获得函数
 e = e || getEventObject(e);
 var x = e.pageX || (e.clientX + (document.documentElement.scrollLeft || document.body.scrollLeft));
 var y = e.pageY || (e.clientY + (document.documentElement.scrollTop || document.body.scrollTop));

 return { 'x':x,'y':y };
}
function setOpacity(elem,level) {//兼容浏览器设置透明值
 if(elem.filters) {
  elem.style.filter = 'alpha(opacity=' + level * 100 + ')';
 } else {
  elem.style.opacity = level;
 }
}
function css(elem,prop) { //css设置函数,可以方便设置css值,并且兼容设置透明值
 for(var i in prop) {
  if(i == 'opacity') {
   setOpacity(elem,prop[i]);
  } else {
   elem.style[i] = prop[i];
  }
 }
 return elem;
}
var magnifier = {
 blV: "v0.0.42",
 m : null,

 blrAboutMe : function(b,d){		
		var s = "";
		s += "<a target='_blank' href='https://littleflute.github.io/vc6/XdHtml/plx/blMagShowImg.js'"
		s += " style='color:lightblue;'";
		s +=">";
		s += " blMagShowImg.js  ";
		s += "</a>"; 
		s += "<a target='_blank' href='https://github.com/littleflute/vc6/edit/master/XdHtml/plx/blMagShowImg.js'"
		s += " style='color:yellow;'";
		s +=">";
		s += "blMagShowImg.js* ";
		s += "</a>"; 
		d.innerHTML = s;
		_on_off_div(b,d);
},
 init:function(magni){
  var m = this.m = magni || {
   cont : null, //装载原始图像的div
   img : null, //放大的图像
   mag : null, //放大框
   scale : 15 //比例值,设置的值越大放大越大,但是这里有个问题就是如果不可以整除时,会产生些很小的白边,目前不知道如何解决
  }
  var _d = m.cont.getElementsByTagName('div')[0];
  css(m.img,{
   'position' : 'absolute',
   'width' : (m.cont.clientWidth * m.scale) + 'px',    //原始图像的宽*比例值
   'height' : (m.cont.clientHeight * m.scale) + 'px'    //原始图像的高*比例值
   })
 
  css(m.mag,{
   'display' : 'none',
   'width' : m.cont.clientWidth + 'px', //m.cont为原始图像,与原始图像等宽
   'height' : m.cont.clientHeight + 'px',
   'position' : 'absolute',
   'left' : 0 + 'px',//放大框的位置
   'top' : 0 + 'px'
   })
 
  var borderWid = _d.offsetWidth - _d.clientWidth;  //获取border的宽
 
  css(_d,{   //_d 为浏览框
   'display' : 'none',        //开始设置为不可见
   'width' : m.cont.clientWidth / m.scale - borderWid + 'px',   //原始图片的宽/比例值 - border的宽度
   'height' : m.cont.clientHeight / m.scale - borderWid + 'px',//原始图片的高/比例值 - border的宽度
   'opacity' : 0.5//设置透明度
   })
 
  m.img.src = m.cont.getElementsByTagName('img')[0].src;//让原始图像的src值给予放大图像
  m.cont.style.cursor = 'crosshair';
 
  m.cont.onmouseover = magnifier.start;
 
 },

 start:function(e){
 
  if(document.all){//只在IE下执行,主要避免IE6的select无法覆盖
   magnifier.createIframe(magnifier.m.img);
  }
 
  this.onmousemove = magnifier.move;//this指向m.cont
  this.onmouseout = magnifier.end;
 },

 move:function(e){
  var pos = getPointerPosition(e);  //事件标准化
  var _d = this.getElementsByTagName('div')[0]; 
  _d.style.display = '';
 
  css(_d ,{
   'background': blColor[2],
   'top' : Math.min(Math.max(pos.y - this.offsetTop - parseInt(_d.style.height) / 2,0),this.clientHeight - _d.offsetHeight) + 'px',
   'left' : Math.min(Math.max(pos.x - this.offsetLeft - parseInt(_d.style.width) / 2,0),this.clientWidth - _d.offsetWidth) + 'px'   //left=鼠标x - this.offsetLeft - 浏览框宽/2,Math.max和Math.min让浏览框不会超出图像
   })
 
  magnifier.m.mag.style.display = '';
 
  css(magnifier.m.img,{
   'top' : - (parseInt(_d.style.top) * magnifier.m.scale) + 'px',
   'left' : - (parseInt(_d.style.left) * magnifier.m.scale) + 'px'
   })
 
 },

 end:function(e){
  this.getElementsByTagName('div')[0].style.display = 'none';
  magnifier.removeIframe(magnifier.m.img);  //销毁iframe
 
  magnifier.m.mag.style.display = 'none';
 },

 createIframe:function(elem){
  var layer = document.createElement('iframe');
  layer.tabIndex = '-1';
  layer.src = 'javascript:false;';
  elem.parentNode.appendChild(layer);
 
  layer.style.width = elem.offsetWidth + 'px';
  layer.style.height = elem.offsetHeight + 'px';
 },

 removeIframe:function(elem){
  var layers = elem.parentNode.getElementsByTagName('iframe');
  while(layers.length >0){
   layers[0].parentNode.removeChild(layers[0]);
  }
 }
}


//--------------
var d1 = blo0.blMDiv(document.body,"id_md1","md1",0,33,500,400,"green");
var s = '<img id="img" src="https://raw.githubusercontent.com/littleflute/blog/master/pics/DSC_1655.JPG"  />';
s += '<div id="Browser">        </div>';
d1.v0 = blo0.blDiv(d1,"v0","v0","grey");
d1.v1 = blo0.blDiv(d1.v0,"magnifier",s,"green");
d1.v1.style.width = "342px";
d1.v1.style.height = "420px";

var i = bl$("img");
i.style.width = "342px";
i.style.height = "420px";
 


var s = '<img id="magnifierImg" />';
var d2 = blo0.blMDiv(document.body,"id_md2","md2",650,0,500,400,"green");
d2.v2 = blo0.blDiv(d2,"mag",s,"red");

function _fnMagShowImg(){ 
	magnifier.init({
       cont : document.getElementById('magnifier'),
       img : document.getElementById('magnifierImg'),
       mag : document.getElementById('mag'),
       scale : 3
       });

var d3 = blo0.blMDiv(document.body,"id_md3","md3",10,330,500,400,"green");
d3.v = blo0.blDiv(d3,d3.id + "v","grey");
blo0.blShowObj2Div(d3.v,magnifier);
 
}

_fnMagShowImg();


