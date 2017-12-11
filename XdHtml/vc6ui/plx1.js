function f1(){
/* _begine_
blo0.blMDiv(document.body,"id_mdiv_plx1","plx1",50,50,200,200,blColor[1]);
_end_*/
}
var t = document.getElementById("id_ta_RunJS");
t.value = f1;
var a = t.value;
var b = a.split("_begine_");
var c = b[1].split("_end_");
t.value = c[0];