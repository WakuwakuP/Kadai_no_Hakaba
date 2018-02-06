// 解答を出力するブロックを取得
var ansForm = document.getElementById('ans-field');

/**
 * euler's Method
 * @param  {fx/dx} func
 * @param  {document} form
 */
function euler (func, form) {
  const a = 0, b = 1, eta = 1;
  let ans = document.createElement('table');

  for (let i = 0; i < 11; i++) {
    const N = Math.pow(2, i);

    const h = (b - a) / N;

    let x = a;
    let y = eta;

    while (x < b) {
      y = y + h * func(x, y);
      x += h;
    }

    const row = ans.insertRow();
    const cel1 = row.insertCell();
    cel1.innerText = "N=" + N + "  ";
    const cel2 = row.insertCell();
    cel2.innerText = "y=" + y + "  ";
    const cel3 = row.insertCell();
    cel3.innerText = ""+ Math.abs(1.64872 - y);
  }
  ansForm.appendChild(ans);
}

function main () {
  const func = function (x, y) {
    return eval(document.getElementById('fx').value);
  }
  ansForm.innerHTML = "";
  euler (func, ansForm);
}
