// 解答を出力するブロックを取得
var ansForm = document.getElementById('ans-field');

/**
 * ガウス・ザイデル法
 * @param  {json}   data  関数データ
 * @param  {Number} eps   許容誤差
 * @param  {Number} loop  ループ回数
 * @return {String}      解
 */
function gaussSeidel(data, eps, loop) {

  const suffix = ['x', 'y', 'z'];
  let x = new Array(1, 1, 1);
  let y = new Array(1, 1, 1);
  let q;
  let ans = '';

  for (let k = 0; k < loop; k++) {
    for (let i = 0; i < data.length; i++) {
      let sum = 0;
      for (let j = 0; j < data.length; j++) {
        if (i != j) {
          sum += data[i][j] * x[j];
        }
      }
      x[i] = (data[i][data.length] - sum) / data[i][i];
    }
    q = 0;

    for (let i = 0; i < data.length; i++) {
      q += Math.abs(x[i] - y[i]);
      y[i] = x[i];
    }
    if (q < eps) {
      for (let i = 0; i < data.length; i++) {
        ans += '<p>' + suffix + ' = ' + x[i] + '</p>';
      }
      break;
    }
  }

  if (ans === '') {
    ans += '<p>Answer of this equation did not converge.</p>';
  }
  return ans;
}

function main() {
  const data = [
    [
      Number(document.getElementById('x_1').value),
      Number(document.getElementById('y_1').value),
      Number(document.getElementById('z_1').value),
      Number(document.getElementById('ans_1').value)
    ],
    [
      Number(document.getElementById('x_2').value),
      Number(document.getElementById('y_2').value),
      Number(document.getElementById('z_2').value),
      Number(document.getElementById('ans_2').value)
    ],
    [
      Number(document.getElementById('x_3').value),
      Number(document.getElementById('y_3').value),
      Number(document.getElementById('z_3').value),
      Number(document.getElementById('ans_3').value)
    ]
  ];
  const eps = Number(document.getElementById('eps').value);
  const loop = Number(document.getElementById('loop').value);

  ansForm.innerHTML = "";
  var answer = gaussSeidel(data, eps, loop);

  ansForm.innerHTML += answer;
}
