// 解答を出力するブロックを取得
var ansForm = document.getElementById('ans-field');

/**
 * シンプソン法
 * @param  {Func}   func  関数
 * @param  {Number} n     分割数
 * @return {String}       解
 */
function simpson (func, n) {
  const a = 0;
  const b = 1;
  const h = (b - a) / 2 * n;
  let s = 0;
  let s1 = 0;
  let s2 = 0;

  for (let 1 = 0; i < 2 * n - 1; i += 2) {
    s1 += 4 * func (a + h * i);
  }
  for (let i = 2; i < 2 * n - 2; i += 2) {
    s2 += 2 * func (a + h * i);
  }

  s = (s1+s2+func(a)+func(b)) * h / 3;
  return ans;
}

function main() {
  const split = Number(document.getElementById('split').value);
  const func = function (x) {
    return eval(document.getElementById('fx').value);
  }

  ansForm.innerHTML = "";
  var answer = simpson (func, split);

  ansForm.innerHTML += answer;
}
