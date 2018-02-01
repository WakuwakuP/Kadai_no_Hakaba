# 数値解析02

## 1.	掃き出し法、ガウス・ザイデル法を用いて解を求める

次の3元連立方程式を掃き出し法、ガウス・ザイデル法を用いて解を求める。

$$
\begin{eqnarray}
{}3x+y+z&=&10 \\x+5y+2z&=&21 \\x+y+5z&=&30
\end{eqnarray}
$$

どちらの方法においても、x=1,y=2,z=5という結果が得られた。

## 2.	講義の例で挙げられた掃き出し法のプログラムの問題

例で挙げられているプログラムでは、入力された対角要素をそのままpivotにしているが、対角要素が0であった場合、0除算が発生し想定外の動作をする可能性が高い。例えば以下の連立方程式

$$
\begin{eqnarray}
{}x+3y+3z&=&-11 \\-2x-4y-2z&=&-14 \\x+y+z&=&-2
\end{eqnarray}
$$

は、掃き出し法で求めていくと3行目の掃き出しで

$$
\begin{eqnarray}
\left[
\begin{array}{ccc}
1 & 0 & -3 & 1 \\0 & 1 & 2 & -4 \\0 & 0 & 0 & 1 \\
\end{array}
\right]
\end{eqnarray}
$$

となってしまい3行3列目の0をpivotとしてしまい0除算が発生してしまう。
このようにならないために、適宜行を交換するようにする。pivotを決める前に、いまpivotにしようとしている列で最も絶対値の大きい行に入れ替える。これによって0除算を回避することができる。
また、この方法でもpivotが0になってしまう場合もある。この場合方程式は不能（解なし）または不定（解が1つに定まらない）になるため、計算を途中で終了して「この式は不定または不能である」という旨のメッセージを表示するようにした。
修正したプログラムは報告書の末尾に添付する。


## 3.	ガウス・ザイデル法で与える初期値について

はじめに初期値について、私が試した数字においてはどのような値を初期値にしても解の精度があるため全く同じではないがほぼ同じ解答が表示された。
繰り返し数は、初期値が解となる値に近いほど少なくなるようだった。1.で挙げた式では初期値5でのみ繰り返し数7回、その周辺では8回となり、10000で試したところ13回という結果になった。

<div style="page-break-before:always"></div>

# 付録

掃き出し法

```html
<!DOCTYPE html>
<html lang="ja">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <meta http-equiv="X-UA-Compatible" content="ie=edge">
  <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css" type="text/css">
  <link rel="stylesheet" href="https://pingendo.com/assets/bootstrap/bootstrap-4.0.0-beta.1.css" type="text/css">

  <title>Sweeping Out Method</title>
</head>
  <body class="bg-faded">
    <div class="">
    <div class="container">
      <div class="row">
        <div class="col-md-12">
          <h1 class="display-1 text-center">掃き出し法</h1>
        </div>
      </div>
    </div>
  </div>
  <div class="py-5">
    <div class="container">
      <div class="row">
        <div class="col-md-12">
          <table>
            <tr>
              <td>1: </td>
              <td><input name="x_1" id="x_1" value="3" size="2" /></td>
              <td>x + </td>
              <td><input name="y_1" id="y_1" value="1" size="2" /></td>
              <td>y + </td>
              <td><input name="z_1" id="z_1" value="1" size="2" /></td>
              <td> = </td>
              <td><input name="ans_1" id="ans_1" value="10" size="2" /></td>
            </tr>
            <tr>
              <td>2: </td>
              <td><input name="x_2" id="x_2" value="1" size="2" /></td>
              <td>x + </td>
              <td><input name="y_2" id="y_2" value="5" size="2" /></td>
              <td>y + </td>
              <td><input name="z_2" id="z_2" value="2" size="2" /></td>
              <td> = </td>
              <td><input name="ans_2" id="ans_2" value="21" size="2" /></td>
            </tr>
            <tr>
              <td>3: </td>
              <td><input name="x_3" id="x_3" value="1" size="2" /></td>
              <td>x + </td>
              <td><input name="y_3" id="y_3" value="2" size="2" /></td>
              <td>y + </td>
              <td><input name="z_3" id="z_3" value="5" size="2" /></td>
              <td> = </td>
              <td><input name="ans_3" id="ans_3" value="30" size="2" /></td>
            </tr>
          </table>
          <div>
            <h3>解</h3>
            <button type="button" onclick="main();">求める</button>
            <div id="ans-field">

            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
  <div class="bg-faded">
    <div class="container">
      <div class="row">
        <div class="col-md-12">
          <div class="text-center">
            <a href="https://www.wakuwakup.net">www.wakuwakup.net</a>
          </div>
          <p class="text-center">© 2017 Naoki Fujisawa</p>
        </div>
      </div>
    </div>
  </div>
  <script src="https://code.jquery.com/jquery-3.1.1.min.js"></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/tether/1.4.0/js/tether.min.js"></script>
  <script src="https://pingendo.com/assets/bootstrap/bootstrap-4.0.0-alpha.6.min.js"></script>
  <script type="text/javascript" src="sweeping-out.js"></script>
</body>
</html>
```

```javascript
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
```

ガウス・ザイデル法
```html
<!DOCTYPE html>
<html lang="ja">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <meta http-equiv="X-UA-Compatible" content="ie=edge">
  <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css" type="text/css">
  <link rel="stylesheet" href="https://pingendo.com/assets/bootstrap/bootstrap-4.0.0-beta.1.css" type="text/css">

  <title>Gauss Seidel Method</title>
</head>
<body class="bg-faded">
  <div class="">
    <div class="container">
      <div class="row">
        <div class="col-md-12">
          <h1 class="display-1 text-center">ガウス・ザイデル法</h1>
        </div>
      </div>
    </div>
  </div>
  <div class="py-5">
    <div class="container">
      <div class="row">
        <div class="col-md-12">
          <table>
            <tr>
              <td>1: </td>
              <td><input name="x_1" id="x_1" value="3" size="2" /></td>
              <td>x + </td>
              <td><input name="y_1" id="y_1" value="1" size="2" /></td>
              <td>y + </td>
              <td><input name="z_1" id="z_1" value="1" size="2" /></td>
              <td> = </td>
              <td><input name="ans_1" id="ans_1" value="10" size="2" /></td>
            </tr>
            <tr>
              <td>2: </td>
              <td><input name="x_2" id="x_2" value="1" size="2" /></td>
              <td>x + </td>
              <td><input name="y_2" id="y_2" value="5" size="2" /></td>
              <td>y + </td>
              <td><input name="z_2" id="z_2" value="2" size="2" /></td>
              <td> = </td>
              <td><input name="ans_2" id="ans_2" value="21" size="2" /></td>
            </tr>
            <tr>
              <td>3: </td>
              <td><input name="x_3" id="x_3" value="1" size="2" /></td>
              <td>x + </td>
              <td><input name="y_3" id="y_3" value="2" size="2" /></td>
              <td>y + </td>
              <td><input name="z_3" id="z_3" value="5" size="2" /></td>
              <td> = </td>
              <td><input name="ans_3" id="ans_3" value="30" size="2" /></td>
            </tr>
          </table>
          <table>
            <tr>
              <td>eps</td>
              <td><input name="eps", id="eps" value="0.000000000000001" /></td>
            </tr>
            <tr>
              <td>loop</td>
              <td><input name="loop", id="loop" value="50" /></td>
            </tr>
          </table>
          <div>
            <h3>解</h3>
            <button type="button" onclick="main();">求める</button>
            <div id="ans-field">

            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
  <div class="bg-faded">
    <div class="container">
      <div class="row">
        <div class="col-md-12">
          <div class="text-center">
            <a href="https://www.wakuwakup.net">www.wakuwakup.net</a>
          </div>
          <p class="text-center">© 2017 Naoki Fujisawa</p>
        </div>
      </div>
    </div>
  </div>
  <script src="https://code.jquery.com/jquery-3.1.1.min.js"></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/tether/1.4.0/js/tether.min.js"></script>
  <script src="https://pingendo.com/assets/bootstrap/bootstrap-4.0.0-alpha.6.min.js"></script>
  <script type="text/javascript" src="gauss-seidel.js"></script>
</body>
</html>
```

```javascript
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
        ans += '<p>' + suffix[i] + ' = ' + x[i] + '</p>';
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
```
