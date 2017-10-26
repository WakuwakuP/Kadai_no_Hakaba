// 解答を出力するブロックを取得
var ansForm = document.getElementById('ans-field');

/**
 * はさみうち法
 * @param  {Number}   low  下限
 * @param  {Number}   high 上限
 * @param  {Number}   ep   許容誤差
 * @param  {x = f(x)} func 関数
 * @return {Number}        解
 */
function falsePosition (low, high, ep, func) {
  var fa = func(low);
  var fb = func(high);

  var x;
  var count = 0;

  ansForm.innerHTML += '<p>';
  while (true) {
    x = (low * func (high) - high * func (low)) / (func (high) -func (low));
    // 途中経過を出力
    ansForm.innerHTML += ("00" + count).slice(-3) + " : " + high.toFixed(10) + ", " + low.toFixed(10) + ", " + x.toFixed(10) + '</br>';

    var fx = func (x);
    if (Math.abs(fx) < ep) {
      ansForm.innerHTML += '</p>';
      break;
    }

    if ((fx > 0) == (fa > 0)) {
      low = x;
      fa = fx;
    } else {
      high = x;
      fb = fx;
    }

    count++ ;
  }

  return x;
}

function main () {
  var high = Number(document.getElementById('high').value);
  var low = Number(document.getElementById('low').value);
  var eps = Number(document.getElementById('eps').value);

  ansForm.innerHTML = "";

  var answer = falsePosition (low, high, eps, function (x) {
     return eval(document.getElementById('fx').value);
  });

  // 結果を出力
  ansForm.innerHTML += '<p>Answer : ' + answer + '</p>';
}
