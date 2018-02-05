Node.prototype.prependChild = function(e){ this.insertBefore(e,this.firstChild); }
const clock = new THREE.Clock();
// シーンを生成
const scene = new THREE.Scene();

// フォグの設定
scene.fog = new THREE.FogExp2(0xEEEEEE, 0.001);

// カメラを生成
const width = window.innerWidth;
const height = window.innerHeight;
const fov = 55;
const aspect = width / height;
const near = 1;
const far = 1400;

const camera = new THREE.PerspectiveCamera(fov, aspect, near, far);
camera.position.set(0,0,800);

// パーティクル設定
const particleCount = 400;
const geometry = new THREE.CubeGeometry(20, 10, 20);
geometry.vertices[0].x*=0.65;
geometry.vertices[0].z*=0.65;
geometry.vertices[1].x*=0.65;
geometry.vertices[1].z*=0.65;
geometry.vertices[4].x*=0.65;
geometry.vertices[4].z*=0.65;
geometry.vertices[5].x*=0.65;
geometry.vertices[5].z*=0.65;
const material = new THREE.MeshPhongMaterial({color:0xD2691E});
const xSpeed = 0.001;
const meshs = [];

for (let i = 0; i < particleCount; i++) {
  let mesh = new THREE.Mesh(geometry, material);
  mesh.position.set(Math.random() * 1000 -500, Math.random() * 1200 - 600, Math.random() * 1000 -500);
  mesh.rotation.set(Math.random()* 360, Math.random()* 360, Math.random()* 360);

  mesh.userData.ySpeed = Math.random() / 2000 + 0.0001;
  mesh.userData.rotateSpeed = (Math.random() * 100 - 50) / 3000;
  mesh.userData.velocity = new THREE.Vector3((Math.random() * 100 - 50) / 200 , - Math.random(), (Math.random() * 100 - 50) / 200);
  meshs.push(mesh);
  scene.add(meshs[i]);
}

// レンダラを追加
const renderer = new THREE.WebGLRenderer();
renderer.setSize(width, height);
renderer.setClearColor( 0xffffff );
document.body.prependChild(renderer.domElement);

// 光源を追加
const directionalLight = new THREE.DirectionalLight( 0xffffff );
directionalLight.position.set(0, 1, 0);
scene.add(directionalLight);

(
  function animate () {
    requestAnimationFrame(animate);

    // ここにアニメーションを記述
    let Count = particleCount;
    let theta = clock.getElapsedTime();
    //camera.position.set (800 * Math.sin(theta / 10), 100, 800 * Math.cos(theta / 10));

    while (Count--) {
      const mesh = meshs[Count];
      if (mesh.position.y < -600){
        mesh.position.set(Math.random() * 1000 -500, 500, Math.random() * 1000 -500);
        mesh.userData.ySpeed = Math.random() / 2000 + 0.0001;
        mesh.userData.rotateSpeed = (Math.random() * 100 - 50) / 3000;
        mesh.userData.velocity.set((Math.random() * 100 - 50) / 200 , - Math.random(), (Math.random() * 100 - 50) / 200);
      }
      mesh.userData.velocity.y -= Math.random() * mesh.userData.ySpeed;
      mesh.rotation.set(mesh.rotation.y + mesh.userData.rotateSpeed, mesh.rotation.y + mesh.userData.rotateSpeed, mesh.rotation.z + mesh.userData.rotateSpeed)
      mesh.position.add(mesh.userData.velocity);
    }

    // 描画
    camera.lookAt(scene.position);
    renderer.render(scene, camera);
  }
)();
