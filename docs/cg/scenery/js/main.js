let mouseX = 0;
let mouseY = 0;
let theta = 0;

const clock = new THREE.Clock();
// シーンを生成
const scene = new THREE.Scene();

// フォグの設定
scene.fog = new THREE.FogExp2(0xfac9f9, 0.0006);

// カメラを生成
const width = window.innerWidth;
const height = window.innerHeight;
const fov = 55;
const aspect = width / height;
const near = 1;
const far = 2000;

const camera = new THREE.PerspectiveCamera(fov, aspect, near, far);
camera.position.set(0,400,800);

// 地面設定
const geometry_ground = new THREE.CubeGeometry(1000, 1, 1000);
const material_ground = new THREE.MeshPhongMaterial({color:0x097a2e});
const mesh_ground = new THREE.Mesh(geometry_ground, material_ground);
meshInitFixity(mesh_ground, 0, -1, 0);
scene.add(mesh_ground);

// 木の設定
const treeData = [
  {x : 0, y : 0, z : 0},
  {x : 100, y : 0, z : 100},
  {x : 200, y : 0, z : 200}
];
const meshs_tree = [];
for (let i = 0; i < treeData.length; i++){
  const geometry_tree = new THREE.CylinderGeometry(0, 25, 80, 20, 1, false);
  const material_tree = new THREE.MeshPhongMaterial({color:0x097a2e});
  let mesh_tree = new THREE.Mesh(geometry_tree, material_tree);
  meshInitFixity(mesh_tree, treeData[i].x, treeData[i].y + 70, treeData[i].z);
  const geometry_trunk = new THREE.CubeGeometry(10, 30, 10);
  const material_trunk = new THREE.MeshPhongMaterial({color:0x7d3a04});
  let mesh_trunk = new THREE.Mesh(geometry_trunk, material_trunk);
  meshInitFixity(mesh_trunk, treeData[i].x, treeData[i].y + 15, treeData[i].z);
  meshs_tree.push({tree : mesh_tree, trunk: mesh_trunk});
  scene.add(meshs_tree[i].tree);
  scene.add(meshs_tree[i].trunk);
}

// 道路の設定

// レンダラを追加
const renderer = new THREE.WebGLRenderer({ antialias: true });
renderer.setSize(width, height);
renderer.setClearColor( 0x90c0ff );
document.body.appendChild(renderer.domElement);

// 光源を追加
const directionalLight = new THREE.DirectionalLight( 0xffffff );
directionalLight.position.set(0, 1, 0);
scene.add(directionalLight);

/**
 * マウス座標を取得するイベント
 */
document.body.addEventListener("mousemove", function(e){
  //座標を取得する
  mouseX = e.pageX;  //X座標
  mouseY = e.pageY;  //Y座標
});

/**
 * マウス位置によってカメラを動かす関数
 */
function cameraRotateMouse () {
  let cameraSpeed = (mouseX / width - 0.5) / 20;;
  theta -= cameraSpeed;
  camera.position.set (800 * Math.sin(theta / 10), 400, 800 * Math.cos(theta / 10));
}

/**
 * メッシュの初期化をする関数
 * @param  {mesh} mesh 個別のメッシュ情報
 */
function meshInit (mesh) {
  mesh.position.set(Math.random() * 1000 -500, Math.random() * 1200 - 600, Math.random() * 1000 -500);
  mesh.rotation.set(Math.random()* 360, Math.random()* 360, Math.random()* 360);
  mesh.userData.ySpeed = Math.random() / 2000 + 0.0001;
  mesh.userData.rotateSpeed = (Math.random() * 100 - 50) / 3000;
  mesh.userData.velocity = new THREE.Vector3((Math.random() * 100 - 50) / 200 , - Math.random(), (Math.random() * 100 - 50) / 200);
}

/**
 * メッシュの初期化をする関数
 * @param  {mesh} mesh 個別のメッシュ情報
 * @param  {[type]} x    xの初期位置
 * @param  {[type]} y    yの初期位置
 * @param  {[type]} z    zの初期位置
 */
function meshInitFixity (mesh, x, y, z) {
  // mesh.position.set(Math.random() * 1000 -500, Math.random() * 1200 - 600, Math.random() * 1000 -500);
  mesh.position.set(x, y, z);
  // mesh.rotation.set(Math.random()* 360, Math.random()* 360, Math.random()* 360);
  mesh.rotation.set(0, 0, 0);
  // mesh.userData.ySpeed = Math.random() / 2000 + 0.0001;
  mesh.userData.ySpeed = 0;
  // mesh.userData.rotateSpeed = (Math.random() * 100 - 50) / 3000;
  mesh.userData.rotateSpeed = 0;
  // mesh.userData.velocity = new THREE.Vector3((Math.random() * 100 - 50) / 200 , - Math.random(), (Math.random() * 100 - 50) / 200);
  mesh.userData.velocity = new THREE.Vector3(0 , 0, 0);
}

/**
 * メッシュを再配置する関数
 * @param {mesh} mesh 個別のメッシュ情報
 */
function meshReset (mesh) {
  mesh.position.set(Math.random() * 1000 -500, 500, Math.random() * 1000 -500);
  mesh.userData.ySpeed = Math.random() / 2000 + 0.0003;
  mesh.userData.rotateSpeed = (Math.random() * 100 - 50) / 3000;
  mesh.userData.velocity.set((Math.random() * 100 - 50) / 200 , - Math.random(), (Math.random() * 100 - 50) / 200);
}

/**
 * メッシュをアニメーションさせる関数
 * @param  {meshs[]} meshs 各メッシュをまとめた配列
 */
function meshAnimate (meshs) {
  // let Count = particleCount;
  // while (Count--) {
  //   const mesh = meshs[Count];
  //   if (mesh.position.y < -600){
  //     meshReset (mesh);
  //   }
  //   mesh.userData.velocity.y -= Math.random() * mesh.userData.ySpeed;
  //   mesh.rotation.set(mesh.rotation.y + mesh.userData.rotateSpeed, mesh.rotation.y + mesh.userData.rotateSpeed, mesh.rotation.z + mesh.userData.rotateSpeed);
  //   mesh.position.add(mesh.userData.velocity);
  // }
}

(
  /**
   * アニメーションさせる関数
   */
  function animate () {
    requestAnimationFrame (animate);  // フレーム更新する関数

    // ここにアニメーションを記述
    //cameraRotateMouse ();
    //meshAnimate (meshs);

    // 描画
    camera.lookAt(scene.position);
    renderer.render(scene, camera);
  }
)();
