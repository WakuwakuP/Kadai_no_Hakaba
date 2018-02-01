// 解答を出力するブロックを取得
var ansForm = document.getElementById('ans-field');

/**
 * 台形法
 * @param  {Function} func  関数
 * @param  {Number}   n     許容誤差
 * @return {String}         解
 */
function trapezoidal (func, n) {
  const a = 0;
  const b = 1;
  const h = (b - a) / n;
  let s = 0;

  for (let i = 0; i < n; i++) {
    s += 2 * func(a + h * i);
  }

  ans = 0.5 * (s + func(a) + func(b)) * h;
  return ans;
}

function main() {
  const split = Number(document.getElementById('split').value);
  const func = function (x) {
    return eval(document.getElementById('fx').value);
  }

  ansForm.innerHTML = "";
  var answer = trapezoidal (func, split);

  ansForm.innerHTML += answer;
}
