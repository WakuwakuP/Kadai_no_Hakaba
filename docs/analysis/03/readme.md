# 数値解析03

## 台形法

|分割数|積分値|相対誤差|
|:---|:---|:---|
|2|0.7826|0.2192|
|4|0.6196|0.0562|
|8|0.5776|0.0142|
|16|0.5670|0.0036|
|32|0.5637|0.0003|
|64|0.5635|0.0001|
|128|0.5635|0.0001|
|256|0.5634|0|

## シンプソン法

|分割数|積分値|相対誤差|
|:---|:---|:---|
|2|0.5653|0.0019|
|4|0.5636|0.0002|
|8|0.5634|0|
|16|0.5634|0|

## 精度比較

シンプソン法の方が少ない分割数で解に収束したため，シンプソン法の方が精度が高いことがわかる．

## 与えられたデータから解を求める

### 台形法

$$
\begin{eqnarray}
S & = & \frac{1-0}{10}\left\{\frac{1}{2}(4.000+2.000)+3.960+3.846+3.670+3.448+3.200+2.941+2.685+2.439+2.210\right\} \\
  & = & \frac{1}{10}\times31.399 \\
  & = & 3.1399
\end{eqnarray}
$$

### シンプソン法

$$
\begin{eqnarray}
S & = & \frac{1-0}{6\times5}\left\{(4.000+2.000)+4(3.960+3.670+3.200+2.685+2.210)+2(3.846+3.448+2.941+2.439)\right\} \\
  & = & \frac{1}{30}\times94.248  \\
  & = & 3.1416
\end{eqnarray}
$$

<div style="page-break-before:always"></div>

## 付録

### 台形法

```html
<!DOCTYPE html>
<html lang="ja">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <meta http-equiv="X-UA-Compatible" content="ie=edge">
  <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css" type="text/css">
  <link rel="stylesheet" href="https://pingendo.com/assets/bootstrap/bootstrap-4.0.0-beta.1.css" type="text/css">

  <title>Tablerapezoidal Method</title>
</head>
<body class="bg-faded">
  <div class="">
    <div class="container">
      <div class="row">
        <div class="col-md-12">
          <h1 class="display-1 text-center">台形法</h1>
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
              <td>f(x)</td>
              <td><input name="fx" id="fx" value="Math.exp(x) * x ** 3" /></td>
            </tr>
            <tr>
              <td>split</td>
              <td><input name="split" id="split" value="128" /></td>
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
  <script type="text/javascript" src="trapezoidal.js"></script>
</body>
</html>
```

```javascript
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
```

### シンプソン法

```html
<!DOCTYPE html>
<html lang="ja">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <meta http-equiv="X-UA-Compatible" content="ie=edge">
  <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css" type="text/css">
  <link rel="stylesheet" href="https://pingendo.com/assets/bootstrap/bootstrap-4.0.0-beta.1.css" type="text/css">

  <title>Simpson's Method</title>
</head>
<body class="bg-faded">
  <div class="">
    <div class="container">
      <div class="row">
        <div class="col-md-12">
          <h1 class="display-1 text-center">シンプソン法</h1>
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
              <td>f(x)</td>
              <td><input name="fx" id="fx" value="Math.exp(x) * x ** 3" /></td>
            </tr>
            <tr>
              <td>split</td>
              <td><input name="split" id="split" value="20" /></td>
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
  <script type="text/javascript" src="trapezoidal.js"></script>
</body>
</html>
```

```javascript
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
```
