let mouseX = 0;
let mouseY = 0;
let theta = 0;

const clock = new THREE.Clock();
// シーンを生成
const scene = new THREE.Scene();

// フォグの設定
scene.fog = new THREE.FogExp2(0xFFFFFF, 0.0006);

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
const material_ground = new THREE.MeshPhongMaterial({color:0xAAAAAA});
const mesh_ground = new THREE.Mesh(geometry_ground, material_ground);
meshInitFixity(mesh_ground, 0, -1, 0);
scene.add(mesh_ground);

// 木の設定
const treeData = [
  {x : 50, y : 0, z : -400},
  {x : 50, y : 0, z : -300},
  {x : 50, y : 0, z : -200},
  {x : 50, y : 0, z : -100},
  {x : 50, y : 0, z : 0},
  {x : 50, y : 0, z : 100},
  {x : 50, y : 0, z : 300},
  {x : 50, y : 0, z : 400},
  {x : 150, y : 0, z : 300},
  {x : 250, y : 0, z : 300},
  {x : 350, y : 0, z : 300},
  {x : 450, y : 0, z : 300},
  {x : -150, y : 0, z : 300},
  {x : -250, y : 0, z : 300},
  {x : -350, y : 0, z : 300},
  {x : -450, y : 0, z : 300},
  {x : -150, y : 0, z : 400},
  {x : -150, y : 0, z : 100},
  {x : -150, y : 0, z : 0},
  {x : -150, y : 0, z : -100},
  {x : -150, y : 0, z : -200},
  {x : -150, y : 0, z : -300},
  {x : -150, y : 0, z : -400},
  {x : -450, y : 0, z : 100},
  {x : -350, y : 0, z : 100},
  {x : -250, y : 0, z : 100},
  {x : 150, y : 0, z : 100},
  {x : 250, y : 0, z : 100},
  {x : 350, y : 0, z : 100},
  {x : 450, y : 0, z : 100}
];
const meshs_tree = [];
for (let i = 0; i < treeData.length; i++){
  const geometry_tree = new THREE.CylinderGeometry(0, 25, 60, 20, 1, false);
  const material_tree = new THREE.MeshPhongMaterial({color:0x097a2e});
  let mesh_tree = new THREE.Mesh(geometry_tree, material_tree);
  meshInitFixity(mesh_tree, treeData[i].x, treeData[i].y + 60, treeData[i].z);
  const geometry_trunk = new THREE.CubeGeometry(10, 30, 10);
  const material_trunk = new THREE.MeshPhongMaterial({color:0x7d3a04});
  let mesh_trunk = new THREE.Mesh(geometry_trunk, material_trunk);
  meshInitFixity(mesh_trunk, treeData[i].x, treeData[i].y + 15, treeData[i].z);
  const geometry_tree_snow = new THREE.CylinderGeometry(4, 25, 60, 20, 1, false);
  const material_tree_snow = new THREE.MeshPhongMaterial({color:0xFFFFFF});
  let mesh_tree_snow = new THREE.Mesh(geometry_tree_snow, material_tree_snow);
  meshInitFixity(mesh_tree_snow, treeData[i].x, treeData[i].y + 70, treeData[i].z);
  meshs_tree.push({tree : mesh_tree, trunk: mesh_trunk, snow: mesh_tree_snow});
  scene.add(meshs_tree[i].tree);
  scene.add(meshs_tree[i].trunk);
  scene.add(meshs_tree[i].snow);
}

// 雪だるまの設定
const snowtreeData = [
  {x : 400, y : 0, z : 400},
  {x : -400, y : 0, z : -200},
  {x : -350, y : 0, z : -300},
  {x : 300, y : 0, z : -300},
  {x : 200, y : 0, z : -220}
];
const meshs_snowtree = [];
for (let i = 0; i < snowtreeData.length; i++){
  const geometry_snowtree1 = new THREE.SphereGeometry(10, 20);
  const geometry_snowtree2 = new THREE.SphereGeometry(15, 20);
  const geometry_snowtree3 = new THREE.CylinderGeometry(5, 6, 10, 20, 1, false);
  const material_snowtree = new THREE.MeshPhongMaterial({color:0xFFFFFF});
  const material_snowtree3 = new THREE.MeshPhongMaterial({color:0x2670ff});
  let mesh_snowtree1 = new THREE.Mesh(geometry_snowtree1, material_snowtree);
  let mesh_snowtree2 = new THREE.Mesh(geometry_snowtree2, material_snowtree);
  let mesh_snowtree3 = new THREE.Mesh(geometry_snowtree3, material_snowtree3);
  meshInitFixity(mesh_snowtree1, snowtreeData[i].x, snowtreeData[i].y + 38, snowtreeData[i].z);
  meshInitFixity(mesh_snowtree2, snowtreeData[i].x, snowtreeData[i].y + 15, snowtreeData[i].z);
  meshInitFixity(mesh_snowtree3, snowtreeData[i].x, snowtreeData[i].y + 50, snowtreeData[i].z);
  meshs_snowtree.push({tree1 : mesh_snowtree1, tree2: mesh_snowtree2, tree3: mesh_snowtree3});
  scene.add(meshs_snowtree[i].tree1);
  scene.add(meshs_snowtree[i].tree2);
  scene.add(meshs_snowtree[i].tree3);
}

// 道路の設定
const roadData = [
  {x1: 500, y1: 250, x2: 0, y2: 150},
  {x1: -100, y1: 250, x2: -500, y2: 150},
  {x1: -100, y1: 500, x2: 0, y2: 250},
  {x1: -100, y1: 150, x2: 0, y2: -500}
];
const meshs_road = [];
for (let i = 0; i < roadData.length; i++){
  const geometry_road = new THREE.CubeGeometry(Math.abs(roadData[i].x1 - roadData[i].x2), 1, Math.abs(roadData[i].y1 - roadData[i].y2));
  const material_road = new THREE.MeshPhongMaterial({color:0x575757});
  let mesh_road = new THREE.Mesh(geometry_road, material_road);
  meshInitFixity(mesh_road, Math.min(roadData[i].x1, roadData[i].x2) + Math.abs(roadData[i].x1 - roadData[i].x2) / 2, 1, Math.min(roadData[i].y1, roadData[i].y2) + Math.abs(roadData[i].y1 - roadData[i].y2) / 2);
  if (Math.abs(roadData[i].x1 - roadData[i].x2) > Math.abs(roadData[i].y1 - roadData[i].y2)) {
    const geometry_line = new THREE.CubeGeometry(Math.abs(roadData[i].x1 - roadData[i].x2), 1, 5);
    const material_line = new THREE.MeshPhongMaterial({color:0xFFFFFF});
    let mesh_line1 = new THREE.Mesh(geometry_line, material_line);
    meshInitFixity(mesh_line1, Math.min(roadData[i].x1, roadData[i].x2) + Math.abs(roadData[i].x1 - roadData[i].x2) / 2, 2, roadData[i].y1);
    let mesh_line2 = new THREE.Mesh(geometry_line, material_line);
    meshInitFixity(mesh_line2, Math.min(roadData[i].x1, roadData[i].x2) + Math.abs(roadData[i].x1 - roadData[i].x2) / 2, 2,  roadData[i].y2);
    meshs_road.push({road: mesh_road, line1: mesh_line1, line2: mesh_line2});
  } else {
    const geometry_line = new THREE.CubeGeometry(5, 1, Math.abs(roadData[i].y1 - roadData[i].y2));
    const material_line = new THREE.MeshPhongMaterial({color:0xFFFFFF});
    let mesh_line1 = new THREE.Mesh(geometry_line, material_line);
    meshInitFixity(mesh_line1, roadData[i].x1, 2, Math.min(roadData[i].y1, roadData[i].y2) + Math.abs(roadData[i].y1 - roadData[i].y2) / 2);
    let mesh_line2 = new THREE.Mesh(geometry_line, material_line);
    meshInitFixity(mesh_line2, roadData[i].x2, 2, Math.min(roadData[i].y1, roadData[i].y2) + Math.abs(roadData[i].y1 - roadData[i].y2) / 2);
    meshs_road.push({road: mesh_road, line1: mesh_line1, line2: mesh_line2});
  }
  scene.add(meshs_road[i].road);
  scene.add(meshs_road[i].line1);
  scene.add(meshs_road[i].line2);
}

//交差点の設定
const crossData = [
  {x1: -100, y1: 150, x2: 0, y2: 250}
];
const meshs_cross = [];
for (let i = 0; i < crossData.length; i++){
  const geometry_cross = new THREE.CubeGeometry(Math.abs(crossData[i].x1 - crossData[i].x2), 1, Math.abs(crossData[i].y1 - crossData[i].y2));
  const material_cross = new THREE.MeshPhongMaterial({color:0x575757});
  let mesh_cross = new THREE.Mesh(geometry_cross, material_cross);
  meshInitFixity(mesh_cross, Math.min(crossData[i].x1, crossData[i].x2) + Math.abs(crossData[i].x1 - crossData[i].x2) / 2, 1, Math.min(crossData[i].y1, crossData[i].y2) + Math.abs(crossData[i].y1 - crossData[i].y2) / 2);
  const geometry_crossline1 = new THREE.CubeGeometry(Math.abs(crossData[i].x1 - crossData[i].x2) / 3, 1, 5);
  const geometry_crossline2 = new THREE.CubeGeometry(5, 1, Math.abs(crossData[i].y1 - crossData[i].y2) / 3);
  const material_crossline = new THREE.MeshPhongMaterial({color:0xFFFFFF});
  let mesh_crossline1 = new THREE.Mesh(geometry_crossline1, material_crossline);
  meshInitFixity(mesh_crossline1, Math.min(crossData[i].x1, crossData[i].x2) + Math.abs(crossData[i].x1 - crossData[i].x2) / 2, 2, Math.min(crossData[i].y1, crossData[i].y2) + Math.abs(crossData[i].y1 - crossData[i].y2) / 2);
  let mesh_crossline2 = new THREE.Mesh(geometry_crossline2, material_crossline);
  meshInitFixity(mesh_crossline2, Math.min(crossData[i].x1, crossData[i].x2) + Math.abs(crossData[i].x1 - crossData[i].x2) / 2, 2, Math.min(crossData[i].y1, crossData[i].y2) + Math.abs(crossData[i].y1 - crossData[i].y2) / 2);
  meshs_cross.push({cross: mesh_cross, crossline1: mesh_crossline1, crossline2: mesh_crossline2});
  scene.add(meshs_cross[i].cross);
  scene.add(meshs_cross[i].crossline1);
  scene.add(meshs_cross[i].crossline2);
}

// レンダラを追加
const renderer = new THREE.WebGLRenderer({ antialias: true });
renderer.setSize(width, height);
renderer.setClearColor( 0x90c0ff );
document.body.appendChild(renderer.domElement);

// 光源を追加
const directionalLight = new THREE.DirectionalLight( 0xffffff );
directionalLight.position.set(0, 1, 0);
scene.add(directionalLight);
var ambientLight = new THREE.AmbientLight(0x666666); // 光源色を指定して生成
scene.add(ambientLight);
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
    cameraRotateMouse ();
    //meshAnimate (meshs);

    // 描画
    camera.lookAt(scene.position);
    renderer.render(scene, camera);
  }
)();
