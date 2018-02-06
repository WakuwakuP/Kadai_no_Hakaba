// 解答を出力するブロックを取得
var ansForm = document.getElementById('ans-field');

/**
 * Runge-Kutta's Method
 * @param  {fx/dx} func
 * @param  {document} form
 */
function rungeKutta (func, form) {
  const a = 1, b = 2, y0 = 1;
  let ans = document.createElement('table');

  for (let i = 0; i < 11; i++) {
    const N = Math.pow(2, i);

    const h = (b - a) / N;

    let x = a;
    let y = y0;

    while (x < b) {
      const k1 = func(x, y);
      const k2 = func(x + h / 2, y + k1 * h / 2);
      const k3 = func(x + h / 2, y + k2 * h / 2);
      const k4 = func(x + h, y + k3 * h);

      y = y + h * (k1 + 2 * k2 + 2 * k3 + k4) /6;
      x += h;
    }

    const row = ans.insertRow();
    const cel1 = row.insertCell();
    cel1.innerText = N;
    const cel2 = row.insertCell();
    cel2.innerText = y;
    const cel3 = row.insertCell();
    cel3.innerText = 3.375 - y;
    const cel4 = row.insertCell();
    cel4.innerText = (3.375 - y) / y * 100;
  }
  ansForm.appendChild(ans);
}

function main () {
  const func = function (x, y) {
    return eval(document.getElementById('fx').value);
  }
  ansForm.innerHTML = "";
  rungeKutta (func, ansForm);
}
