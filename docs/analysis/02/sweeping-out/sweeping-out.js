// 解答を出力するブロックを取得
var ansForm = document.getElementById('ans-field');

/**
 * 掃き出し法
 * @param  {json} data 関数データ
 * @return {String}      解
 */
function sweepingOut(data) {
  const suffix = ['x', 'y', 'z'];
  let ans = '';
  const searchBigCoef = (v, data) => {
    let big = 0.0;
    let ret = -1;
    for (let i = v; i < data.length; i++) {
      if (Math.abs(data[i][v]) > big) {
        big = Math.abs(data[i][v]);
        ret = i;
      }
    }
    return ret;
  };

  const swapEquation = (v, w, data) => {
    for (let i = 0; i < data[0].length; i++) {
      let tmp = data[v][i];
      data[v][i] = data[w][i];
      data[w][i] = tmp;
    }
    return data;
  };

  for (let i = 0; i < data.length; i++) {
    let pivot;
    let p = searchBigCoef(i, data);
    let j, k;

    if (p == -1) {
      ans += "<p>This equation is inconsistent or indefinite.</p>";
      return ans;
    }

    data = swapEquation(i, p, data);
    pivot = data[i][i];
    for (let j = i; j < data[0].length; j++) {
      data[i][j] = data[i][j] / pivot;
    }
    for (let k = 0; k < data.length; k++) {
      if (k - i != 0) {
        let aik = data[k][i];
        for (let j = i; j < data[0].length; j++) {
          data[k][j] = data[k][j] - aik * data[i][j];
        }
      }
    }
  }

  for (let i = 0; i < data.length; i++) {
    ans += '<p>' + suffix[i] + ' = ' + data[i][data.length] + '</p>';
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

  ansForm.innerHTML = "";
  var answer = sweepingOut(data);

  ansForm.innerHTML += answer;
}
