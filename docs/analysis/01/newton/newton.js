// 解答を出力するブロックを取得
var ansForm = document.getElementById('ans-field');

/**
 * ニュートン法
 * @param  {Number}   x_0    初期値
 * @param  {Number}   ep     許容誤差
 * @param  {x = f(x)} func   与えられた関数
 * @param  {x = f(x)} func_d 与えられた関数の導関数
 * @return {Number}          解
 */
function newton (x_0, ep, func, func_d) {
  var count = 0;
  while (true) {
    var fx = func(x_0);
    var dx = func_d(x_0);

    var x_1 = x_0 - fx / dx;
    count++;

    ansForm.innerHTML += '<p>' + ("00" + count).slice(-3) + ' : ' + x_0.toFixed(10) + '</p>';

    if (Math.abs(x_1 - x_0) < ep) { break; }

    x_0 = x_1;
  }

  console.log(count + '回 : ' + x_0);

  return x_0;
}

function main () {
  var x_0 = Number(document.getElementById('x_0').value);
  var eps = Number(document.getElementById('eps').value);
  var func = function (x) {
    return eval(document.getElementById('fx').value);
  }
  var func_d = function (x) {
    return eval(document.getElementById('dfx').value);
  }

  ansForm.innerHTML = "";

  var answer = newton (x_0, eps, func, func_d);

  ansForm.innerHTML += "Answer : " + answer;
}
