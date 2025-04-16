let sequence = [];
let userSequence = [];
let acceptingInput = false;

const colors = ["red", "green", "blue", "yellow"];
let colorCount = 4;
let speedSetting = "medium";

let level = 1;
let score = 0;

document.getElementById("start-button").addEventListener("click", startGame);

function startGame() {
  sequence = [];
  userSequence = [];
  acceptingInput = false;
  level = 1;
  score = 0;

  speedSetting = document.getElementById("speed").value;
  colorCount = parseInt(document.getElementById("color-count").value);

  document.getElementById("menu-screen").style.display = "none";
  document.getElementById("game-screen").style.display = "block";

  updateUI();
  nextRound();
}

function nextRound() {
  const activeColors = colors.slice(0, colorCount);
  const newColor = activeColors[Math.floor(Math.random() * activeColors.length)];
  sequence.push(newColor);
  userSequence = [];
  acceptingInput = false;

  setTimeout(() => playSequence(), 500);
}

function playSequence() {
  let i = 0;
  const delay = speedSetting === "fast" ? 400 : speedSetting === "medium" ? 700 : 1000;

  const interval = setInterval(() => {
    const color = sequence[i];
    const button = document.querySelector(`.color-button[data-color="${color}"]`);

    button.classList.add("active");
    setTimeout(() => button.classList.remove("active"), delay / 1.5);

    i++;
    if (i >= sequence.length) {
      clearInterval(interval);
      acceptingInput = true;
    }
  }, delay);
}

document.querySelectorAll(".color-button").forEach(btn => {
  btn.addEventListener("click", () => {
    if (!acceptingInput) return;

    const color = btn.getAttribute("data-color");
    userSequence.push(color);

    btn.classList.add("active");
    setTimeout(() => btn.classList.remove("active"), 200);

    checkUserInput();
  });
});

function checkUserInput() {
  const index = userSequence.length - 1;
  if (userSequence[index] !== sequence[index]) {
    alert("Perdu ! 😢\nTu étais au niveau " + level + "\nScore : " + score);
    resetGame();
    return;
  }

  if (userSequence.length === sequence.length) {
    score += userSequence.length;
    level++;
    updateUI();
    setTimeout(() => {
      nextRound();
    }, 1000);
  }
}

function resetGame() {
  document.getElementById("game-screen").style.display = "none";
  document.getElementById("menu-screen").style.display = "flex";
  sequence = [];
  userSequence = [];
  acceptingInput = false;
  level = 1;
  score = 0;
  updateUI();
}

function updateUI() {
  document.getElementById("level-display").textContent = level;
  document.getElementById("score-display").textContent = score;
}
