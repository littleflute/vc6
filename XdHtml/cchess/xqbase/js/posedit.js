var PIECE_NAME = [
	"oo", "xx", null, null, null, null, null, null,
	"rk", "ra", "rb", "rn", "rr", "rc", "rp", null,
	"bk", "ba", "bb", "bn", "br", "bc", "bp", null
];

var html = "";
for (var y = RANK_TOP; y <= RANK_BOTTOM; y ++) {
	html += "<tr>";
	for (var x = FILE_LEFT; x <= FILE_RIGHT; x ++) {
		html += "<td><img width=\"41\" height=\"41\" sq=\"" + COORD_XY(x, y) + "\"></td>";
	}
	html += "</tr>";
}
$("#board").html(html);

html = "";
for (var i = 1; i < 3; i ++) {
	html += "<tr>";
	for (var j = 0; j < 8; j ++) {
		html += "<td><img width=\"41\" height=\"41\" pc=\"" + (i * 8 + j) + "\"></td>";
	}
	html += "</tr>";
}
$("#pieces").html(html);

var sqSelected = 0, pcSelected = 0;
var changed = false, deleting = false;
var imgSquares = new Array(256), imgPieces = new Array(24);
var imgDelete = $("img[pc='15']"), imgSearch = $("img[pc='23']");
var pos = new Position();

function setClick(img, fn) {
	img.mousedown((function(img_, fn_) {
		return function() {
			(fn_)(img_);
		};
	})(img, fn));
	img.contextmenu(function() {
		return false;
	});
}

function setSrc(img, name, selected) {
	img.prop("src", "http://www.xqbase.com/images/pieces/" + name + (selected ? "s.gif" : ".gif"));
}

function updateFen() {
	$("#fen").val(pos.toFen() + " - - 0 1");
	changed = true;
}

function drawSquare(sq, selected) {
	setSrc(imgSquares[sq], PIECE_NAME[pos.squares[sq]], selected);
}

function drawPiece(pc, selected) {
	setSrc(imgPieces[pc], PIECE_NAME[pc], selected);
}

function drawDelete(selected) {
	setSrc(imgDelete, "xx", selected);
}

function unselectSquare() {
	drawSquare(sqSelected);
	sqSelected = 0;
}

function unselectPiece() {
	drawPiece(pcSelected);
	pcSelected = 0;
}

function unselectDelete() {
	drawDelete();
	deleting = false;
}

function flushBoard() {
	sqSelected = 0;
	for (var sq = 0; sq < 256; sq ++) {
		if (IN_BOARD(sq)) {
			drawSquare(sq);
		}
	}
	$("#player_" + pos.sdPlayer).prop("checked", true);
	$("#player_" + (1 - pos.sdPlayer)).prop("checked", false);
	changed = false;
}

function flushFen() {
	$("#fen").val(pos.toFen() + " - - 0 1");
	flushBoard();
}

function clickSquare(sq) {
	if (sq == sqSelected) {
		unselectSquare();
		return; 
	}

	if (sqSelected > 0) {
		var mv = MOVE(sqSelected, sq);
		if (!changed && pos.legalMove(mv) && pos.makeMove(mv)) {
			drawSquare(sq);
			unselectSquare();
			search();
			return;
		}

		var pc = pos.squares[sq];
		if (pc > 0) {
			pos.addPiece(sq, pc, DEL_PIECE);
		}
		pc = pos.squares[sqSelected];
		pos.addPiece(sqSelected, pc, DEL_PIECE);
		pos.addPiece(sq, pc);
		drawSquare(sq);
		unselectSquare();
		updateFen();
		return;
	}

	if (pcSelected > 0) {
		var pc = pos.squares[sq];
		if (pc > 0) {
			pos.addPiece(sq, pc, DEL_PIECE);
		}
		pos.addPiece(sq, pcSelected);
		drawSquare(sq);
		unselectPiece();
		updateFen();
		return;
	}

	if (deleting) {
		var pc = pos.squares[sq];
		if (pc > 0) {
			pos.addPiece(sq, pc, DEL_PIECE);
			drawSquare(sq);
			unselectDelete();
			updateFen();
		}
		return;
	}

	if (pos.squares[sq] > 0) {
		drawSquare(sq, true);
		sqSelected = sq;
	}
}

function clickPiece(pc) {
	if (pc == pcSelected) {
		unselectPiece();
		return;
	}
	if (pcSelected > 0) {
		unselectPiece();
	} else if (deleting) {
		unselectDelete();
	} else if (sqSelected > 0) {
		unselectSquare();
	}
	drawPiece(pc, true);
	pcSelected = pc;
}

function clickDelete() {
	if (deleting) {
		unselectDelete();
		return;
	}
	if (sqSelected > 0) {
		pos.addPiece(sqSelected, pos.squares[sqSelected], DEL_PIECE);
		unselectSquare();
		return;
	}
	if (pcSelected > 0) {
		unselectPiece();
	}
	drawDelete(true);
	deleting = true;
}

function changePlayer(sd) {
	if (sd == pos.sdPlayer) {
		return;
	}
	pos.changeSide();
	updateFen();
}

function changeFen() {
	pos.fromFen($("#fen").val());
	flushBoard();
}

function search() {
	location.href = target + encodeURIComponent(pos.toFen() + " - - 0 1");
}

for (var y = RANK_TOP; y <= RANK_BOTTOM; y ++) {
	for (var x = FILE_LEFT; x <= FILE_RIGHT; x ++) {
		var sq = COORD_XY(x, y);
		imgSquares[sq] = $("img[sq='" + sq + "']");
		setClick(imgSquares[sq], function(img) {
			clickSquare(parseInt(img.attr("sq")));
		});
	}
}

$("#player_0").click(function() {
	changePlayer(0);
});
$("#player_1").click(function() {
	changePlayer(1);
});

for (var pc = 8; pc <= 22; pc ++) {
	imgPieces[pc] = $("img[pc='" + pc + "']");
	if (pc == 15) {
		continue;
	}
	setClick(imgPieces[pc], function(img) {
		clickPiece(parseInt(img.attr("pc")));
	});
	drawPiece(pc, false);
}
setClick(imgDelete, clickDelete);
drawDelete();
setClick(imgSearch, search);
imgSearch.prop("src", "/images/search.gif");

$("#fen").val(fen);
$("#fen").on("propertychange input", changeFen);
changeFen();

$("#search").click(search);
$("#revert").click(function() {
	pos.fromFen(fen);
	flushFen();
});
$("#startup").click(function() {
	pos.fromFen("rnbakabnr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RNBAKABNR w");
	flushFen();
});
$("#clear").click(function() {
	pos.clearBoard();
	pos.setIrrev();
	flushFen();
});
