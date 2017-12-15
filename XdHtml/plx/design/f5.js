var f5 = function(b,d){
	//f5.js v0.0.2
	d.innerHTML = "f5.js: ->" + b.id + ":" + d.id;
};

var ta = bl$( "id_ta_4_NewClass" );
if( ta ){
	ta.f5 = f5;
	ta.value = ta.f5;
}
