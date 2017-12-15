var f1 = function(b,d){
	//f1.js v0.0.22

	d.innerHTML = "";
	var d1 = blo0.blDiv(d,d.id + "_d1",":: ",blGrey[5]);
	var b0 = blo0.blBtn(d,d.id + "_b0","光标位置",blGrey[0]);
	b0.onclick = function(){d1.innerHTML = "光标位置:" + _getCursorPosition (ta); };
	var b1 = blo0.blBtn(d,d.id + "_b1","设置光标到第3位置",blGrey[0]);
	b1.onclick = function(){_sel (ta,3,3); };
	var b2 = blo0.blBtn(d,d.id + "_b2","选中字符0-2的位置",blGrey[0]);
	b2.onclick = function(){_sel (ta,0,2); };
	var b3 = blo0.blBtn(d,d.id + "_b3","添加'你好'到光标后面",blGrey[0]);
	b3.onclick = function(){_add (ta,'你好'); };
	var b4 = blo0.blBtn(d,d.id + "_b4","删除光标前2个字符",blGrey[0]);
	b4.onclick = function(){_del (ta,2); };
	var b5 = blo0.blBtn(d,d.id + "_b5","删除光标后2个字符",blGrey[0]);
	b5.onclick = function(){_del (ta,-2); };
	var b6 = blo0.blBtn(d,d.id + "_b6","选中字符'function'的位置",blGrey[0]);
	b6.onclick = function(){ _selString (ta,'function'); };
	var btnUpdate = blo0.blBtn(d,d.id+"_Update","UpdateLink","brown");
	btnUpdate.onclick = function(){
			var href = "https://github.com/littleflute/vc6/edit/master/XdHtml/plx/design/f1.js";
			var l = blo0.blLink(d1,d1.id+"_link","Update",href,"Salmon");
		};

	_on_off_div(b,d);

	/*
     * 获取光标位置
     * @Method _getCursorPosition
     * @param t element
     * @return number
     */
    function _getCursorPosition (t){
        if (document.selection) {
            t.focus();
            var ds = document.selection;
            var range = ds.createRange();
            var stored_range = range.duplicate();
            stored_range.moveToElementText(t);
            stored_range.setEndPoint("EndToEnd", range);
            t.selectionStart = stored_range.text.length - range.text.length;
            t.selectionEnd = t.selectionStart + range.text.length;
            return t.selectionStart;
        } else return t.selectionStart
    }
	/*
     * 设置光标位置
     * @Method _setCursorPosition
     * @param t element
     * @param p number
     * @return
     */
    function _setCursorPosition(t, p){
        _sel(t,p,p);
    }

    /*
     * 选中 s 到 z 位置的文字
     * @Method sel
     * @param t element
     * @param s number
     * @param z number
     * @return
     */
   function _sel (t,s,z) {
	if(document.selection){
            var range = t.createTextRange();
            range.moveEnd('character', -t.value.length);        
            range.moveEnd('character', z);
            range.moveStart('character', s);
            range.select();
        }else{
            t.setSelectionRange(s,z);
            t.focus();
        }
    }

	/*
     * 删除光标 前面或者后面的 n 个字符
     * @Method del
     * @param t element
     * @param n number  n>0 后面 n<0 前面
     * @return
     * 重新设置 value 的时候 scrollTop 的值会被清0
     */
    function _del (t, n){
        var p = _getCursorPosition(t);
        var s = t.scrollTop;
        var val = t.value;
        t.value = n > 0 ? val.slice(0, p - n) + val.slice(p):
                        val.slice(0, p) + val.slice(p - n);
        _setCursorPosition(t ,p - (n < 0 ? 0 : n));
        firefox=navigator.userAgent.toLowerCase().match(/firefox\/([\d\.]+)/) && setTimeout(function(){
            if(t.scrollTop != s) t.scrollTop=s;
        },10)
    }
	/*
     * 选中一个字符串
     * @Method _selString
     * @param t element
     * @param s String
     * @return
     */
    function _selString(t, s){
        var index = t.value.indexOf(s);
        index != -1 ? _sel(t, index, index + s.length) : false;
    }

    /*
     * 插入到光标后面
     * @Method _add
     * @param t element
     * @param txt String
     * @return
     */
    function _add (t, txt){
        var val = t.value;
        if(document.selection){
            t.focus()
            document.selection.createRange().text = txt; 
        } else {
            var cp = t.selectionStart;
            var ubbLength = t.value.length;
            var s = t.scrollTop;
            t.value = t.value.slice(0,t.selectionStart) + txt + t.value.slice(t.selectionStart, ubbLength);
            this.setCursorPosition(t, cp + txt.length);
            firefox=navigator.userAgent.toLowerCase().match(/firefox\/([\d\.]+)/) && setTimeout(function(){
                if(t.scrollTop != s) t.scrollTop=s;
            },0)

        };
    }
};

var ta = bl$( "id_ta_4_NewClass" );
if( ta ){
	ta.f1 = f1;
	ta.value = ta.f1;
}
