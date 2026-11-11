<!DOCTYPE html>
<html lang="ja">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>模擬コンビニエンスストア 〜金銭処理・おつり・両替トレーニング〜</title>
  <!-- Tailwind CSS -->
  <script src="https://cdn.tailwindcss.com"></script>
  <!-- Font Awesome Icons -->
  <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.4.0/css/all.min.css">
  <!-- Google Fonts -->
  <link rel="preconnect" href="https://fonts.googleapis.com">
  <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
  <link href="https://fonts.googleapis.com/css2?family=M+PLUS+Rounded+1c:wght@400;500;700;800&display=swap" rel="stylesheet">

  <script>
    tailwind.config = {
      theme: {
        extend: {
          fontFamily: {
            sans: ['"M PLUS Rounded 1c"', 'sans-serif'],
          },
          colors: {
            convenii: {
              green: '#00873c',
              orange: '#f37021',
              blue: '#005bac',
              red: '#e60012',
              bg: '#f4f7f6'
            }
          }
        }
      }
    }
  </script>

  <style>
    body {
      font-family: 'M PLUS Rounded 1c', sans-serif;
      background-color: #eef2f5;
      user-select: none;
    }

    /* 日本の硬貨・お札のスタイリング */
    .coin {
      display: inline-flex;
      align-items: center;
      justify-content: center;
      border-radius: 50%;
      font-weight: 800;
      box-shadow: 0 4px 6px -1px rgba(0, 0, 0, 0.2), inset 0 2px 4px rgba(255, 255, 255, 0.6);
      cursor: pointer;
      transition: all 0.15s ease;
      position: relative;
    }
    .coin:hover {
      transform: translateY(-2px) scale(1.05);
    }
    .coin:active {
      transform: translateY(1px) scale(0.98);
    }

    .coin-500 {
      background: linear-gradient(135deg, #f5d77f 0%, #d4af37 50%, #aa820a 100%);
      color: #4a3b00;
      border: 2px solid #fff3ba;
    }
    .coin-100 {
      background: linear-gradient(135deg, #e6e8eb 0%, #b0b5bc 50%, #7d848e 100%);
      color: #2b303a;
      border: 2px solid #ffffff;
    }
    .coin-50 {
      background: linear-gradient(135deg, #d8dce1 0%, #9aa0a8 50%, #686e77 100%);
      color: #1f2328;
      border: 2px solid #ffffff;
    }
    .coin-50::after {
      content: '';
      width: 22%;
      height: 22%;
      background-color: #2d3748;
      border-radius: 50%;
      position: absolute;
      box-shadow: inset 0 1px 2px rgba(0,0,0,0.5);
    }
    .coin-10 {
      background: linear-gradient(135deg, #e29363 0%, #b85c28 50%, #7c350c 100%);
      color: #3b1401;
      border: 2px solid #f7c0a1;
    }
    .coin-5 {
      background: linear-gradient(135deg, #f3d068 0%, #c89d28 50%, #8c680a 100%);
      color: #423000;
      border: 2px solid #ffe89e;
    }
    .coin-5::after {
      content: '';
      width: 24%;
      height: 24%;
      background-color: #2d3748;
      border-radius: 50%;
      position: absolute;
      box-shadow: inset 0 1px 2px rgba(0,0,0,0.5);
    }
    .coin-1 {
      background: linear-gradient(135deg, #f0f4f8 0%, #cbd5e1 50%, #94a3b8 100%);
      color: #334155;
      border: 1px solid #ffffff;
    }

    /* 紙幣 */
    .bill {
      border-radius: 6px;
      font-weight: 700;
      box-shadow: 0 4px 6px -1px rgba(0, 0, 0, 0.15), inset 0 0 0 2px rgba(255,255,255,0.4);
      cursor: pointer;
      transition: all 0.15s ease;
      display: flex;
      flex-direction: column;
      justify-content: space-between;
      padding: 6px 10px;
      position: relative;
      overflow: hidden;
    }
    .bill:hover {
      transform: translateY(-2px) scale(1.03);
    }
    .bill:active {
      transform: translateY(1px);
    }
    .bill-10000 {
      background: linear-gradient(135deg, #f3e5ab 0%, #d4b46a 100%);
      color: #4a3800;
      border: 1px solid #b89742;
    }
    .bill-5000 {
      background: linear-gradient(135deg, #e1bee7 0%, #ab47bc 100%);
      color: #ffffff;
      border: 1px solid #8e24aa;
    }
    .bill-1000 {
      background: linear-gradient(135deg, #b2ebf2 0%, #0097a7 100%);
      color: #00363a;
      border: 1px solid #00838f;
    }

    /* レジ液晶ディスプレイ風 */
    .register-display {
      background-color: #1a2a1d;
      color: #5af07a;
      font-family: 'Courier New', Courier, monospace;
      text-shadow: 0 0 8px rgba(90, 240, 122, 0.6);
      border: 4px solid #334155;
      box-shadow: inset 0 2px 6px rgba(0,0,0,0.8);
    }

    /* カスタムスクロールバー */
    ::-webkit-scrollbar {
      width: 6px;
      height: 6px;
    }
    ::-webkit-scrollbar-track {
      background: #f1f1f1;
      border-radius: 10px;
    }
    ::-webkit-scrollbar-thumb {
      background: #cbd5e1;
      border-radius: 10px;
    }
    ::-webkit-scrollbar-thumb:hover {
      background: #94a3b8;
    }

    @keyframes pulse-subtle {
      0%, 100% { transform: scale(1); }
      50% { transform: scale(1.03); }
    }
    .animate-pulse-subtle {
      animation: pulse-subtle 2s infinite ease-in-out;
    }
  </style>
</head>
<body class="min-h-screen flex flex-col text-slate-800">

  <!-- ヘッダー -->
  <header class="bg-gradient-to-r from-convenii-green via-emerald-600 to-teal-700 text-white shadow-md sticky top-0 z-50">
    <div class="max-w-7xl mx-auto px-4 py-3 flex flex-wrap items-center justify-between gap-2">
      <div class="flex items-center space-x-3">
        <div class="bg-white text-convenii-green p-2 rounded-xl shadow-md">
          <i class="fa-solid font-black fa-store text-2xl"></i>
        </div>
        <div>
          <span class="text-xs bg-convenii-orange text-white px-2 py-0.5 rounded-full font-bold">12月学習テーマ</span>
          <h1 class="text-lg md:text-xl font-extrabold tracking-wide">模擬コンビニ：金銭処理アプリ</h1>
        </div>
      </div>

      <!-- モード切り替えタブ -->
      <nav class="flex bg-emerald-900/40 p-1 rounded-xl gap-1 overflow-x-auto max-w-full">
        <button id="nav-clerk" onclick="switchMode('clerk')" class="nav-btn px-3 py-1.5 rounded-lg text-sm font-bold transition flex items-center gap-1.5 bg-white text-convenii-green shadow">
          <i class="fa-solid fa-cash-register"></i>
          <span>店員さん</span>
        </button>
        <button id="nav-customer" onclick="switchMode('customer')" class="nav-btn px-3 py-1.5 rounded-lg text-sm font-bold transition flex items-center gap-1.5 text-white hover:bg-white/10">
          <i class="fa-solid fa-cart-shopping"></i>
          <span>お客さん</span>
        </button>
        <button id="nav-drill" onclick="switchMode('drill')" class="nav-btn px-3 py-1.5 rounded-lg text-sm font-bold transition flex items-center gap-1.5 text-white hover:bg-white/10">
          <i class="fa-solid fa-brain"></i>
          <span>両替・計算ドリル</span>
        </button>
        <button id="nav-free" onclick="switchMode('free')" class="nav-btn px-3 py-1.5 rounded-lg text-sm font-bold transition flex items-center gap-1.5 text-white hover:bg-white/10">
          <i class="fa-solid fa-calculator"></i>
          <span>自由レジ＆両替機</span>
        </button>
      </nav>
    </div>
  </header>

  <!-- メインコンテンツ領域 -->
  <main class="flex-1 max-w-7xl w-full mx-auto p-3 md:p-6 flex flex-col gap-6">

    <!-- 1. 店員さんモード -->
    <section id="mode-clerk" class="mode-section flex flex-col gap-6">
      <!-- 学習目標バナー -->
      <div class="bg-amber-50 border-l-4 border-amber-500 p-4 rounded-r-xl shadow-sm flex flex-col md:flex-row justify-between items-start md:items-center gap-3">
        <div>
          <span class="text-amber-800 text-xs font-bold uppercase tracking-wider">Mission & Math Skill</span>
          <h2 class="text-slate-800 font-bold text-base md:text-lg">【店員役】商品のスキャンとおつりの正確な渡し</h2>
          <p class="text-slate-600 text-xs md:text-sm">お買い上げ合計を計算し、お客様からの預かり金に対して**正確なおつり**を硬貨・紙幣で選んで渡しましょう！</p>
        </div>
        <div class="flex items-center gap-4 bg-white px-4 py-2 rounded-lg shadow-inner border border-amber-200 self-end md:self-auto">
          <div class="text-center">
            <div class="text-xs text-slate-500 font-bold">スコア</div>
            <div id="clerk-score" class="text-xl font-extrabold text-convenii-green">0</div>
          </div>
          <div class="h-8 w-px bg-slate-200"></div>
          <div class="text-center">
            <div class="text-xs text-slate-500 font-bold">連続成功</div>
            <div id="clerk-streak" class="text-xl font-extrabold text-convenii-orange">0</div>
          </div>
        </div>
      </div>

      <div class="grid grid-cols-1 lg:grid-cols-12 gap-6">
        <!-- 左側：レジカウンター＆お客様 -->
        <div class="lg:col-span-5 flex flex-col gap-4">
          <!-- お客様登場エリア -->
          <div class="bg-white p-5 rounded-2xl shadow-sm border border-slate-200 flex flex-col items-center text-center relative overflow-hidden">
            <div class="absolute top-3 left-3 bg-slate-100 text-slate-600 px-2.5 py-1 rounded-full text-xs font-bold">
              <i class="fa-solid fa-user me-1"></i>お客さま
            </div>
            
            <div class="w-20 h-20 bg-amber-100 rounded-full flex items-center justify-center my-2 text-4xl shadow-inner border-2 border-amber-300">
              <span id="customer-avatar">🧍‍♂️</span>
            </div>
            
            <div class="bg-emerald-50 border border-emerald-200 rounded-2xl p-3 w-full my-2 relative">
              <div class="absolute -top-2 left-1/2 -translate-x-1/2 w-4 h-4 bg-emerald-50 border-t border-l border-emerald-200 rotate-45"></div>
              <p id="customer-dialog" class="text-sm font-bold text-slate-700">「お願いします！これ買います。」</p>
            </div>

            <!-- カゴの中身（商品リスト） -->
            <div class="w-full mt-2">
              <div class="text-xs font-bold text-slate-500 text-left mb-2 flex justify-between items-center">
                <span>買い物カゴの中身</span>
                <span id="item-count-badge" class="bg-slate-200 text-slate-700 text-xs px-2 py-0.5 rounded-full">3点</span>
              </div>
              <div id="cart-items" class="space-y-2 max-h-48 overflow-y-auto pr-1">
                <!-- 動的追加 -->
              </div>
            </div>
          </div>

          <!-- レジ本体ディスプレイ -->
          <div class="bg-slate-800 p-4 rounded-2xl shadow-lg border-4 border-slate-700 text-white">
            <div class="register-display p-4 rounded-xl mb-3 font-mono">
              <div class="flex justify-between text-xs text-emerald-400 opacity-80 border-b border-emerald-900 pb-1 mb-2">
                <span>POS REGISTER v2.4 (手動おつり計算モード)</span>
                <span id="reg-clock">12:00</span>
              </div>
              <div class="flex justify-between items-center text-sm mb-1">
                <span class="text-slate-300">合計金額 (税込):</span>
                <span class="text-xl font-bold text-white"><span id="display-total">0</span> 円</span>
              </div>
              <div class="flex justify-between items-center text-sm mb-1">
                <span class="text-slate-300">お預かり:</span>
                <span class="text-lg font-bold text-yellow-300"><span id="display-paid">0</span> 円</span>
              </div>
              <div class="flex justify-between items-center text-base pt-1 border-t border-emerald-800/80 mt-1">
                <span class="text-emerald-300 font-bold">おつり:</span>
                <div class="flex items-center gap-2">
                  <span class="text-2xl font-black text-emerald-400"><span id="display-change-needed">？？？</span> 円</span>
                  <button id="btn-show-hint" onclick="toggleChangeHint()" class="text-xs bg-emerald-800/80 hover:bg-emerald-700 text-emerald-200 px-2 py-1 rounded-lg border border-emerald-600 transition">
                    <i class="fa-solid fa-eye me-1"></i>計算の答え
                  </button>
                </div>
              </div>
            </div>

            <!-- お客様からの支払い（トレイ表示） -->
            <div class="bg-slate-900/80 p-3 rounded-xl border border-slate-700">
              <div class="text-xs font-bold text-slate-400 mb-1.5 flex items-center justify-between">
                <span><i class="fa-solid fa-hand-holding-dollar text-amber-400 me-1"></i>お客様から渡されたお金</span>
              </div>
              <div id="customer-paid-money" class="flex flex-wrap gap-2 min-h-[48px] items-center p-2 bg-slate-950/60 rounded-lg border border-slate-800">
                <!-- 渡されたお金アイコン -->
              </div>
            </div>
          </div>

          <!-- 暗算・電卓サポートツール -->
          <div class="bg-white p-4 rounded-2xl shadow-sm border border-slate-200">
            <div class="flex justify-between items-center border-b pb-2 mb-2">
              <span class="text-xs font-bold text-slate-700"><i class="fa-solid fa-calculator text-convenii-green me-1"></i>計算用メモ・電卓</span>
              <button onclick="clearClerkCalc()" class="text-[10px] text-slate-500 hover:text-slate-800">クリア</button>
            </div>
            <div class="flex items-center gap-2">
              <div id="clerk-calc-disp" class="flex-1 bg-slate-100 p-2 rounded-lg font-mono text-right text-base font-bold text-slate-800 border min-h-[38px]">
                0
              </div>
              <button onclick="pressClerkCalc('-')" class="bg-slate-200 hover:bg-slate-300 font-bold px-3 py-2 rounded-lg text-sm">－</button>
              <button onclick="calcClerkResult()" class="bg-convenii-green hover:bg-emerald-700 text-white font-bold px-3 py-2 rounded-lg text-sm">＝</button>
            </div>
            <div class="grid grid-cols-5 gap-1 mt-2">
              <button onclick="pressClerkCalc(7)" class="bg-slate-50 hover:bg-slate-100 p-1.5 rounded text-xs font-bold">7</button>
              <button onclick="pressClerkCalc(8)" class="bg-slate-50 hover:bg-slate-100 p-1.5 rounded text-xs font-bold">8</button>
              <button onclick="pressClerkCalc(9)" class="bg-slate-50 hover:bg-slate-100 p-1.5 rounded text-xs font-bold">9</button>
              <button onclick="pressClerkCalc(4)" class="bg-slate-50 hover:bg-slate-100 p-1.5 rounded text-xs font-bold">4</button>
              <button onclick="pressClerkCalc(5)" class="bg-slate-50 hover:bg-slate-100 p-1.5 rounded text-xs font-bold">5</button>
              <button onclick="pressClerkCalc(6)" class="bg-slate-50 hover:bg-slate-100 p-1.5 rounded text-xs font-bold">6</button>
              <button onclick="pressClerkCalc(1)" class="bg-slate-50 hover:bg-slate-100 p-1.5 rounded text-xs font-bold">1</button>
              <button onclick="pressClerkCalc(2)" class="bg-slate-50 hover:bg-slate-100 p-1.5 rounded text-xs font-bold">2</button>
              <button onclick="pressClerkCalc(3)" class="bg-slate-50 hover:bg-slate-100 p-1.5 rounded text-xs font-bold">3</button>
              <button onclick="pressClerkCalc(0)" class="bg-slate-50 hover:bg-slate-100 p-1.5 rounded text-xs font-bold">0</button>
            </div>
          </div>
        </div>

        <!-- 右側：おつり受け渡しトレイ＆お金ボタン選択 -->
        <div class="lg:col-span-7 flex flex-col gap-4">
          <!-- おつり選択カウンター -->
          <div class="bg-white p-5 rounded-2xl shadow-sm border border-slate-200 flex flex-col gap-4 flex-1">
            <div class="flex justify-between items-center border-b pb-3">
              <div>
                <h3 class="font-bold text-slate-800 text-lg flex items-center gap-2">
                  <i class="fa-solid fa-coins text-amber-500"></i> おつりをトレーに出す
                </h3>
                <p class="text-xs text-slate-500">硬貨やお札をクリックして、ぴったりのおつりを作ってください。</p>
              </div>
              <button onclick="clearSelectedChange()" class="text-xs text-rose-600 hover:bg-rose-50 px-2.5 py-1.5 rounded-lg border border-rose-200 font-bold transition">
                <i class="fa-solid fa-rotate-left me-1"></i>やり直す
              </button>
            </div>

            <!-- 現在選んだおつり合計 -->
            <div class="bg-emerald-50/70 p-4 rounded-xl border border-emerald-200 flex items-center justify-between">
              <div>
                <span class="text-xs text-emerald-800 font-bold block">現在選んでいるおつり合計</span>
                <span id="current-given-change" class="text-3xl font-black text-convenii-green">0 <span class="text-sm">円</span></span>
              </div>
              <div id="change-status-badge" class="text-xs font-bold px-3 py-1.5 rounded-full bg-slate-200 text-slate-600">
                未入力
              </div>
            </div>

            <!-- 選んだおつりの視覚表示トレイ -->
            <div class="bg-amber-50/50 p-3 rounded-xl border-2 border-dashed border-amber-200 min-h-[90px] flex flex-wrap gap-2 items-center align-content-start">
              <div id="selected-change-tray" class="flex flex-wrap gap-2 items-center w-full">
                <span class="text-xs text-slate-400 w-full text-center py-4">下のお金をクリックしておつりをのせてね</span>
              </div>
            </div>

            <!-- お金選択パネル (お札・コイン) -->
            <div class="space-y-3 mt-auto">
              <!-- 紙幣 -->
              <div>
                <span class="text-xs font-bold text-slate-500 block mb-1">【紙幣】</span>
                <div class="grid grid-cols-3 gap-2">
                  <button onclick="addChangeMoney(10000)" class="bill bill-10000 h-14">
                    <span class="text-xs">壱万円</span>
                    <span class="text-right font-black text-sm">10000円</span>
                  </button>
                  <button onclick="addChangeMoney(5000)" class="bill bill-5000 h-14">
                    <span class="text-xs">五千円</span>
                    <span class="text-right font-black text-sm">5000円</span>
                  </button>
                  <button onclick="addChangeMoney(1000)" class="bill bill-1000 h-14">
                    <span class="text-xs">千円</span>
                    <span class="text-right font-black text-sm">1000円</span>
                  </button>
                </div>
              </div>

              <!-- 硬貨 -->
              <div>
                <span class="text-xs font-bold text-slate-500 block mb-1">【硬貨】</span>
                <div class="grid grid-cols-6 gap-2">
                  <button onclick="addChangeMoney(500)" class="flex flex-col items-center gap-1 group">
                    <div class="coin coin-500 w-12 h-12 text-xs">500</div>
                    <span class="text-[10px] font-bold text-slate-600">500円</span>
                  </button>
                  <button onclick="addChangeMoney(100)" class="flex flex-col items-center gap-1 group">
                    <div class="coin coin-100 w-11 h-11 text-xs">100</div>
                    <span class="text-[10px] font-bold text-slate-600">100円</span>
                  </button>
                  <button onclick="addChangeMoney(50)" class="flex flex-col items-center gap-1 group">
                    <div class="coin coin-50 w-10 h-10 text-[10px]">50</div>
                    <span class="text-[10px] font-bold text-slate-600">50円</span>
                  </button>
                  <button onclick="addChangeMoney(10)" class="flex flex-col items-center gap-1 group">
                    <div class="coin coin-10 w-10 h-10 text-[10px]">10</div>
                    <span class="text-[10px] font-bold text-slate-600">10円</span>
                  </button>
                  <button onclick="addChangeMoney(5)" class="flex flex-col items-center gap-1 group">
                    <div class="coin coin-5 w-9 h-9 text-[10px]">5</div>
                    <span class="text-[10px] font-bold text-slate-600">5円</span>
                  </button>
                  <button onclick="addChangeMoney(1)" class="flex flex-col items-center gap-1 group">
                    <div class="coin coin-1 w-8 h-8 text-[10px]">1</div>
                    <span class="text-[10px] font-bold text-slate-600">1円</span>
                  </button>
                </div>
              </div>
            </div>

            <!-- アクションボタン -->
            <div class="pt-2 flex gap-3">
              <button id="btn-submit-change" onclick="submitChangeAnswer()" class="flex-1 bg-convenii-orange hover:bg-orange-600 text-white font-extrabold py-3.5 px-6 rounded-xl shadow-md transition text-center text-lg flex items-center justify-center gap-2">
                <i class="fa-solid fa-handshake"></i> おつりを渡す！
              </button>
              <button onclick="nextClerkCustomer()" class="bg-slate-200 hover:bg-slate-300 text-slate-700 font-bold px-4 py-3.5 rounded-xl transition text-sm">
                次のお客様 <i class="fa-solid fa-arrow-right ms-1"></i>
              </button>
            </div>

          </div>
        </div>
      </div>
    </section>

    <!-- 2. お客さんモード -->
    <section id="mode-customer" class="mode-section hidden flex-col gap-6">
      <div class="bg-sky-50 border-l-4 border-sky-500 p-4 rounded-r-xl shadow-sm flex flex-col md:flex-row justify-between items-start md:items-center gap-3">
        <div>
          <span class="text-sky-800 text-xs font-bold uppercase tracking-wider">Customer Experience</span>
          <h2 class="text-slate-800 font-bold text-base md:text-lg">【客役】スマートなお買い物と小銭の払い方</h2>
          <p class="text-slate-600 text-xs md:text-sm">商品を選んで、財布から**小銭が多く残らないスマートな支払い額**を出してみよう！（例: 780円に対して1030円支払うなど）</p>
        </div>
        <div class="bg-white px-4 py-2 rounded-lg shadow-inner border border-sky-200 flex items-center gap-3">
          <div class="text-xs font-bold text-slate-500">所持金（お財布）</div>
          <div id="customer-wallet-amount" class="text-xl font-extrabold text-sky-600">3,000円</div>
        </div>
      </div>

      <div class="grid grid-cols-1 lg:grid-cols-12 gap-6">
        <!-- 商品棚エリア -->
        <div class="lg:col-span-7 bg-white p-5 rounded-2xl shadow-sm border border-slate-200 flex flex-col gap-4">
          <h3 class="font-bold text-slate-800 text-base flex items-center justify-between">
            <span><i class="fa-solid fa-store text-convenii-green me-2"></i>コンビニの商品棚</span>
            <span class="text-xs text-slate-400 font-normal">タップしてカゴに入れる</span>
          </h3>

          <div id="store-shelf" class="grid grid-cols-2 sm:grid-cols-3 gap-3">
            <!-- 動的に商品カード生成 -->
          </div>
        </div>

        <!-- カゴとお会計支払いエリア -->
        <div class="lg:col-span-5 flex flex-col gap-4">
          <div class="bg-white p-5 rounded-2xl shadow-sm border border-slate-200 flex flex-col gap-4">
            <h3 class="font-bold text-slate-800 text-base border-b pb-2 flex justify-between items-center">
              <span><i class="fa-solid fa-basket-shopping text-convenii-orange me-2"></i>あなたのマイカゴ</span>
              <button onclick="clearCustomerCart()" class="text-xs text-rose-500 font-bold">空にする</button>
            </h3>

            <div id="customer-cart-list" class="space-y-2 min-h-[100px] max-h-[180px] overflow-y-auto">
              <div class="text-center py-6 text-slate-400 text-xs">商品棚から食べ物や飲み物を選んでね</div>
            </div>

            <div class="bg-slate-100 p-3 rounded-xl space-y-1 text-sm font-bold">
              <div class="flex justify-between text-slate-600">
                <span>小計:</span>
                <span id="cust-subtotal">0円</span>
              </div>
              <div class="flex justify-between text-slate-800 text-base pt-1 border-t border-slate-200">
                <span>合計金額:</span>
                <span id="cust-total" class="text-xl text-convenii-red font-black">0円</span>
              </div>
            </div>

            <!-- 支払いお金の選択 -->
            <div class="border-t pt-3 space-y-3">
              <div class="flex justify-between items-center">
                <span class="text-xs font-bold text-slate-700">レジに出すお金を選んでね:</span>
                <span id="cust-payment-sum" class="text-sm font-extrabold text-convenii-blue">出す金額: 0円</span>
              </div>

              <!-- 出すお金の表示トレー -->
              <div id="cust-pay-tray" class="bg-slate-50 p-2 rounded-lg border min-h-[50px] flex flex-wrap gap-1.5 items-center">
                <span class="text-xs text-slate-400 w-full text-center">下のお金をクリックして出す</span>
              </div>

              <!-- お財布のお金ボタン -->
              <div class="grid grid-cols-4 gap-1.5">
                <button onclick="addCustPayment(1000)" class="bg-cyan-100 hover:bg-cyan-200 text-cyan-900 border border-cyan-300 rounded p-1.5 text-xs font-bold text-center">1000円札</button>
                <button onclick="addCustPayment(500)" class="bg-amber-100 hover:bg-amber-200 text-amber-900 border border-amber-300 rounded p-1.5 text-xs font-bold text-center">500円玉</button>
                <button onclick="addCustPayment(100)" class="bg-slate-200 hover:bg-slate-300 text-slate-800 border border-slate-300 rounded p-1.5 text-xs font-bold text-center">100円玉</button>
                <button onclick="addCustPayment(50)" class="bg-slate-200 hover:bg-slate-300 text-slate-800 border border-slate-300 rounded p-1.5 text-xs font-bold text-center">50円玉</button>
                <button onclick="addCustPayment(10)" class="bg-orange-100 hover:bg-orange-200 text-orange-900 border border-orange-300 rounded p-1.5 text-xs font-bold text-center">10円玉</button>
                <button onclick="addCustPayment(5)" class="bg-amber-100 hover:bg-amber-200 text-amber-900 border border-amber-300 rounded p-1.5 text-xs font-bold text-center">5円玉</button>
                <button onclick="addCustPayment(1)" class="bg-slate-100 hover:bg-slate-200 text-slate-800 border border-slate-300 rounded p-1.5 text-xs font-bold text-center">1円玉</button>
                <button onclick="clearCustPayment()" class="bg-rose-100 hover:bg-rose-200 text-rose-700 border border-rose-300 rounded p-1.5 text-xs font-bold text-center">クリア</button>
              </div>

              <!-- ヒント機能 -->
              <div id="smart-payment-hint" class="bg-amber-50 p-2.5 rounded-lg border border-amber-200 text-xs text-amber-800 hidden">
                <div id="hint-text">スマートヒントがここに表示されます</div>
              </div>

              <button onclick="submitCustomerPay()" class="w-full bg-convenii-blue hover:bg-blue-700 text-white font-extrabold py-3 rounded-xl shadow transition">
                レジでお支払いする！
              </button>
            </div>
          </div>
        </div>
      </div>
    </section>

    <!-- 3. 両替・金銭計算ドリル -->
    <section id="mode-drill" class="mode-section hidden flex-col gap-6">
      <div class="bg-purple-50 border-l-4 border-purple-500 p-4 rounded-r-xl shadow-sm flex flex-col md:flex-row justify-between items-start md:items-center gap-3">
        <div>
          <span class="text-purple-800 text-xs font-bold uppercase tracking-wider">Math & Money Drill</span>
          <h2 class="text-slate-800 font-bold text-base md:text-lg">【ドリル】おつり暗算・両替・最小枚数マスター</h2>
          <p class="text-slate-600 text-xs md:text-sm">おつりの計算、お札と小銭の両替（1,000円＝100円玉10枚など）、最少枚数で作る練習問題に挑戦！</p>
        </div>
        <div class="flex items-center gap-3 bg-white px-4 py-2 rounded-lg shadow-inner border border-purple-200">
          <div class="text-xs font-bold text-purple-700">正解数</div>
          <div id="drill-score" class="text-2xl font-black text-purple-600">0 / 0</div>
        </div>
      </div>

      <div class="max-w-2xl mx-auto w-full bg-white p-6 md:p-8 rounded-3xl shadow-sm border border-slate-200 flex flex-col gap-6">
        <!-- ドリル問題コンテナ -->
        <div id="drill-card" class="space-y-6">
          <div class="flex justify-between items-center border-b pb-3">
            <span id="drill-category" class="bg-purple-100 text-purple-800 text-xs font-bold px-3 py-1 rounded-full">両替の考え方</span>
            <span id="drill-q-num" class="text-xs text-slate-400 font-bold">第 1 問</span>
          </div>

          <!-- 問題本文 -->
          <div class="text-center py-4">
            <div id="drill-question-text" class="text-xl md:text-2xl font-extrabold text-slate-800 leading-snug">
              1,000円札 1枚 を、すべて100円玉に両替すると 何枚 になりますか？
            </div>
            <div id="drill-visual-hint" class="mt-4 flex justify-center gap-2 flex-wrap">
              <!-- イラストヒント -->
            </div>
          </div>

          <!-- 回答選択肢 or 数値入力 -->
          <div id="drill-answers-container" class="grid grid-cols-1 sm:grid-cols-2 gap-3 pt-2">
            <!-- 動的選択肢ボタン -->
          </div>

          <!-- 正誤判定フィードバック -->
          <div id="drill-feedback" class="hidden p-4 rounded-xl text-center font-bold text-base"></div>
        </div>

        <button id="drill-next-btn" onclick="nextDrillQuestion()" class="hidden w-full bg-purple-600 hover:bg-purple-700 text-white font-extrabold py-3.5 rounded-xl shadow transition text-center">
          次の問題へ進む <i class="fa-solid fa-arrow-right ms-2"></i>
        </button>
      </div>
    </section>

    <!-- 4. 自由レジ＆両替シミュレーター（対面ロールプレイ・授業用） -->
    <section id="mode-free" class="mode-section hidden flex-col gap-6">
      <div class="bg-teal-50 border-l-4 border-teal-500 p-4 rounded-r-xl shadow-sm">
        <h2 class="text-slate-800 font-bold text-base md:text-lg">【自由レジ＆両替機】対面ロールプレイ＆ツール</h2>
        <p class="text-slate-600 text-xs md:text-sm">実際の授業やお買い物ごっこで使えるレジシステムです。金額を自由入力してお会計したり、お札をクリックして硬貨に両替（分解）する実験ができます。</p>
      </div>

      <div class="grid grid-cols-1 lg:grid-cols-12 gap-6">
        <!-- 自由電卓レジ -->
        <div class="lg:col-span-6 bg-white p-5 rounded-2xl shadow-sm border border-slate-200 flex flex-col gap-4">
          <h3 class="font-bold text-slate-800 text-base flex items-center gap-2 border-b pb-2">
            <i class="fa-solid fa-calculator text-teal-600"></i> インタラクティブ電卓レジ
          </h3>

          <div class="register-display p-4 rounded-xl font-mono space-y-2">
            <div class="flex justify-between text-sm">
              <span class="text-slate-400">商品合計:</span>
              <span id="free-total-disp" class="text-xl text-white font-bold">0 円</span>
            </div>
            <div class="flex justify-between text-sm">
              <span class="text-slate-400">お預かり額:</span>
              <span id="free-paid-disp" class="text-xl text-yellow-300 font-bold">0 円</span>
            </div>
            <div class="flex justify-between text-base border-t border-emerald-800 pt-1">
              <span class="text-emerald-300 font-bold">おつり:</span>
              <span id="free-change-disp" class="text-2xl text-emerald-400 font-black">0 円</span>
            </div>
          </div>

          <!-- 金額入力テンキー -->
          <div class="space-y-3">
            <div class="flex gap-2">
              <button onclick="setFreeField('total')" id="btn-field-total" class="flex-1 py-2 px-3 rounded-lg text-xs font-bold border-2 border-teal-500 bg-teal-50 text-teal-800">1. 合計金額を入力中</button>
              <button onclick="setFreeField('paid')" id="btn-field-paid" class="flex-1 py-2 px-3 rounded-lg text-xs font-bold border border-slate-200 bg-slate-50 text-slate-600">2. 預かり金額を入力中</button>
            </div>

            <div class="grid grid-cols-3 gap-2">
              <button onclick="pressNumpad(7)" class="bg-slate-100 hover:bg-slate-200 text-slate-800 font-bold py-3 rounded-xl text-lg">7</button>
              <button onclick="pressNumpad(8)" class="bg-slate-100 hover:bg-slate-200 text-slate-800 font-bold py-3 rounded-xl text-lg">8</button>
              <button onclick="pressNumpad(9)" class="bg-slate-100 hover:bg-slate-200 text-slate-800 font-bold py-3 rounded-xl text-lg">9</button>
              <button onclick="pressNumpad(4)" class="bg-slate-100 hover:bg-slate-200 text-slate-800 font-bold py-3 rounded-xl text-lg">4</button>
              <button onclick="pressNumpad(5)" class="bg-slate-100 hover:bg-slate-200 text-slate-800 font-bold py-3 rounded-xl text-lg">5</button>
              <button onclick="pressNumpad(6)" class="bg-slate-100 hover:bg-slate-200 text-slate-800 font-bold py-3 rounded-xl text-lg">6</button>
              <button onclick="pressNumpad(1)" class="bg-slate-100 hover:bg-slate-200 text-slate-800 font-bold py-3 rounded-xl text-lg">1</button>
              <button onclick="pressNumpad(2)" class="bg-slate-100 hover:bg-slate-200 text-slate-800 font-bold py-3 rounded-xl text-lg">2</button>
              <button onclick="pressNumpad(3)" class="bg-slate-100 hover:bg-slate-200 text-slate-800 font-bold py-3 rounded-xl text-lg">3</button>
              <button onclick="pressNumpad(0)" class="bg-slate-100 hover:bg-slate-200 text-slate-800 font-bold py-3 rounded-xl text-lg">0</button>
              <button onclick="pressNumpad('00')" class="bg-slate-100 hover:bg-slate-200 text-slate-800 font-bold py-3 rounded-xl text-lg">00</button>
              <button onclick="clearNumpad()" class="bg-rose-100 hover:bg-rose-200 text-rose-700 font-bold py-3 rounded-xl text-sm">C (消去)</button>
            </div>
          </div>
        </div>

        <!-- 視覚的両替・分解シミュレーター -->
        <div class="lg:col-span-6 bg-white p-5 rounded-2xl shadow-sm border border-slate-200 flex flex-col gap-4">
          <h3 class="font-bold text-slate-800 text-base flex items-center gap-2 border-b pb-2">
            <i class="fa-solid fa-arrows-split-up-and-left text-amber-500"></i> 両替（お金の分解・まとめ）マシン
          </h3>
          <p class="text-xs text-slate-500">お札や硬貨をクリックすると、同額の小さな単位のお金に分解されます！</p>

          <div class="space-y-4">
            <div class="bg-slate-50 p-4 rounded-xl border border-slate-200 flex flex-col items-center gap-3">
              <span class="text-xs font-bold text-slate-600">分解したいお金を選んでクリック！</span>
              <div class="flex flex-wrap gap-2 justify-center">
                <button onclick="demonstrateExchange(1000)" class="bill bill-1000 h-12 w-28 text-xs">1000円札</button>
                <button onclick="demonstrateExchange(500)" class="coin coin-500 w-12 h-12 text-xs">500円</button>
                <button onclick="demonstrateExchange(100)" class="coin coin-100 w-10 h-10 text-xs">100円</button>
                <button onclick="demonstrateExchange(50)" class="coin coin-50 w-9 h-9 text-[10px]">50円</button>
                <button onclick="demonstrateExchange(10)" class="coin coin-10 w-9 h-9 text-[10px]">10円</button>
              </div>
            </div>

            <!-- 両替結果表示アニメーション領域 -->
            <div id="exchange-result-box" class="bg-amber-50/60 border-2 border-amber-200 p-4 rounded-xl min-h-[160px] flex flex-col items-center justify-center text-center">
              <span class="text-slate-400 text-xs">上のお金ボタンを押すと両替の仕方が表示されます</span>
            </div>
          </div>
        </div>
      </div>
    </section>

  </main>

  <!-- 結果フィードバックダイアログ Modal -->
  <div id="modal-result" class="fixed inset-0 bg-slate-900/60 backdrop-blur-sm z-50 flex items-center justify-center p-4 hidden">
    <div class="bg-white rounded-3xl max-w-sm w-full p-6 text-center shadow-2xl border-4 border-emerald-400 flex flex-col items-center gap-4 animate-pulse-subtle">
      <div id="modal-icon" class="w-16 h-16 bg-emerald-100 text-convenii-green rounded-full flex items-center justify-center text-3xl">
        <i class="fa-solid fa-circle-check"></i>
      </div>
      <div>
        <h3 id="modal-title" class="text-xl font-black text-slate-800">大正解！</h3>
        <p id="modal-msg" class="text-sm text-slate-600 mt-1">正確なおつりを渡せました！</p>
      </div>
      <button onclick="closeModal()" class="w-full bg-convenii-green hover:bg-emerald-700 text-white font-extrabold py-3 rounded-xl shadow transition">
        つぎへ進む
      </button>
    </div>
  </div>

  <script>
    // --- Web Audio API サウンド効果 ---
    const audioCtx = new (window.AudioContext || window.webkitAudioContext)();

    function playSound(type) {
      if (audioCtx.state === 'suspended') {
        audioCtx.resume();
      }
      const osc = audioCtx.createOscillator();
      const gain = audioCtx.createGain();
      osc.connect(gain);
      gain.connect(audioCtx.destination);

      const now = audioCtx.currentTime;

      if (type === 'beep') { // レジのスキャン音
        osc.type = 'sine';
        osc.frequency.setValueAtTime(1800, now);
        gain.gain.setValueAtTime(0.15, now);
        gain.gain.exponentialRampToValueAtTime(0.001, now + 0.08);
        osc.start(now);
        osc.stop(now + 0.08);
      } else if (type === 'coin') { // チャリン音
        osc.type = 'triangle';
        osc.frequency.setValueAtTime(2400, now);
        osc.frequency.exponentialRampToValueAtTime(1200, now + 0.05);
        gain.gain.setValueAtTime(0.2, now);
        gain.gain.exponentialRampToValueAtTime(0.001, now + 0.06);
        osc.start(now);
        osc.stop(now + 0.06);
      } else if (type === 'success') { // ファンファーレ
        const notes = [523.25, 659.25, 783.99, 1046.50];
        notes.forEach((freq, idx) => {
          const o = audioCtx.createOscillator();
          const g = audioCtx.createGain();
          o.connect(g);
          g.connect(audioCtx.destination);
          o.type = 'sine';
          o.frequency.setValueAtTime(freq, now + idx * 0.08);
          g.gain.setValueAtTime(0.15, now + idx * 0.08);
          g.gain.exponentialRampToValueAtTime(0.001, now + idx * 0.08 + 0.2);
          o.start(now + idx * 0.08);
          o.stop(now + idx * 0.08 + 0.2);
        });
      } else if (type === 'error') { // 失敗音
        osc.type = 'sawtooth';
        osc.frequency.setValueAtTime(180, now);
        gain.gain.setValueAtTime(0.2, now);
        gain.gain.exponentialRampToValueAtTime(0.001, now + 0.25);
        osc.start(now);
        osc.stop(now + 0.25);
      }
    }

    // --- コンビニ商品データ ---
    const STORE_ITEMS = [
      { id: 1, name: 'しゃけおにぎり', price: 140, icon: '🍙' },
      { id: 2, name: '緑茶 500ml', price: 160, icon: '🍵' },
      { id: 3, name: 'ミックスサンド', price: 280, icon: '🥪' },
      { id: 4, name: '幕の内弁当', price: 540, icon: '🍱' },
      { id: 5, name: 'からあげパック', price: 220, icon: '🍗' },
      { id: 6, name: '濃厚バニラアイス', price: 190, icon: '🍨' },
      { id: 7, name: 'ポテトチップス', price: 150, icon: '🥔' },
      { id: 8, name: 'ファミチキ風チキン', price: 240, icon: '🥩' },
      { id: 9, name: 'メロンパン', price: 130, icon: '🥐' },
      { id: 10, name: 'ビニール傘', price: 700, icon: '☂️' }
    ];

    const CUSTOMER_AVATARS = ['🧍‍♂️', '🧍‍♀️', '👵', '👴', '👩‍💼', '👨‍🎓', '👧'];

    // --- アプリ状態管理 ---
    let currentMode = 'clerk';

    // 店員モード状態
    let clerkScore = 0;
    let clerkStreak = 0;
    let currentCart = [];
    let currentTotal = 0;
    let currentPaid = 0;
    let changeNeeded = 0;
    let selectedChangeMoney = []; // プレイヤーが選んだおつり配列
    let isHintShown = false;
    let clerkCalcInput = '';

    // お客さんモード状態
    let custCart = [];
    let custPaymentMoney = [];

    // ドリル状態
    let drillIndex = 0;
    let drillScoreCount = 0;

    // 自由レジ状態
    let freeTotal = 0;
    let freePaid = 0;
    let activeFreeField = 'total';

    // --- 初期化 ---
    window.onload = function() {
      initClerkMode();
      initCustomerShelf();
      loadDrillQuestion();
      updateClock();
      setInterval(updateClock, 1000);
    };

    function updateClock() {
      const now = new Date();
      const timeStr = now.toLocaleTimeString('ja-JP', { hour: '2-digit', minute: '2-digit' });
      const el = document.getElementById('reg-clock');
      if (el) el.textContent = timeStr;
    }

    // モード切替
    function switchMode(mode) {
      currentMode = mode;
      document.querySelectorAll('.mode-section').forEach(sec => sec.classList.add('hidden'));
      document.querySelectorAll('.nav-btn').forEach(btn => {
        btn.classList.remove('bg-white', 'text-convenii-green', 'shadow');
        btn.classList.add('text-white', 'hover:bg-white/10');
      });

      document.getElementById(`mode-${mode}`).classList.remove('hidden');
      document.getElementById(`mode-${mode}`).classList.add('flex');

      const activeNav = document.getElementById(`nav-${mode}`);
      activeNav.classList.add('bg-white', 'text-convenii-green', 'shadow');
      activeNav.classList.remove('text-white', 'hover:bg-white/10');
    }

    // ==========================================
    // 1. 店員さんモード Logic
    // ==========================================
    // スマートな預かり金の計算（客がいくら払うか）
    function calculateSmartCustomerPayment(total) {
      if (total <= 0) return 1000;
      
      const candidates = [];
      const bill500 = Math.ceil(total / 500) * 500;
      const bill1000 = Math.ceil(total / 1000) * 1000;
      const bill5000 = Math.ceil(total / 5000) * 5000;
      const bill10000 = Math.ceil(total / 10000) * 10000;
      
      if (bill500 >= total) candidates.push(bill500);
      if (bill1000 >= total) candidates.push(bill1000);
      if (bill5000 >= total) candidates.push(bill5000);
      if (bill10000 >= total) candidates.push(bill10000);

      const rem10 = total % 10;
      const rem50 = total % 50;
      const rem100 = total % 100;

      if (rem10 > 0 && total + rem10 >= total) candidates.push(total + rem10);
      if (rem50 > 0 && total + rem50 >= total) candidates.push(total + rem50);
      if (rem100 > 0 && total + rem100 >= total) candidates.push(total + rem100);
      if (rem100 > 0 && bill1000 + rem100 >= total) candidates.push(bill1000 + rem100);

      const unique = Array.from(new Set(candidates.filter(c => c >= total)));
      if (unique.length === 0) return Math.ceil(total / 1000) * 1000 || 1000;

      return unique[Math.floor(Math.random() * unique.length)];
    }

    // 店員用：買い物カゴの表示
    function renderClerkCart() {
      const container = document.getElementById('cart-items');
      const badge = document.getElementById('item-count-badge');
      if (!container) return;

      container.innerHTML = '';
      if (badge) badge.textContent = `${currentCart.length}点`;

      currentCart.forEach(item => {
        const row = document.createElement('div');
        row.className = 'flex justify-between items-center bg-slate-50 p-2 rounded-lg border text-xs font-bold';
        row.innerHTML = `
          <span>${item.icon} ${item.name}</span>
          <span class="text-convenii-green font-extrabold">${item.price}円</span>
        `;
        container.appendChild(row);
      });
    }

    // 店員用：客の支払ったお金のグラフィック表示
    function renderCustomerPaidTray(amount) {
      const container = document.getElementById('customer-paid-money');
      if (!container) return;
      container.innerHTML = '';

      let remaining = amount;
      const denoms = [10000, 5000, 1000, 500, 100, 50, 10, 5, 1];

      denoms.forEach(d => {
        const count = Math.floor(remaining / d);
        if (count > 0) {
          remaining %= d;
          for (let i = 0; i < count; i++) {
            if (d >= 1000) {
              const el = document.createElement('div');
              el.className = `bill bill-${d} text-[10px] py-0.5 px-1.5 h-7 font-bold flex items-center shadow-sm`;
              el.textContent = `${d}円`;
              container.appendChild(el);
            } else {
              const el = document.createElement('div');
              el.className = `coin coin-${d} text-[10px] w-7 h-7 font-bold`;
              el.textContent = d;
              container.appendChild(el);
            }
          }
        }
      });
    }

    function initClerkMode() {
      selectedChangeMoney = [];
      isHintShown = false;
      clerkCalcInput = '';
      document.getElementById('clerk-calc-disp').textContent = '0';
      updateSelectedChangeDisplay();

      // お客様アバター切り替え
      const avatar = CUSTOMER_AVATARS[Math.floor(Math.random() * CUSTOMER_AVATARS.length)];
      document.getElementById('customer-avatar').textContent = avatar;

      // ランダムに2〜4つの商品をカートに入れる
      const itemNum = Math.floor(Math.random() * 3) + 2;
      currentCart = [];
      for (let i = 0; i < itemNum; i++) {
        const item = STORE_ITEMS[Math.floor(Math.random() * STORE_ITEMS.length)];
        currentCart.push(item);
      }

      // レンジ計算
      currentTotal = currentCart.reduce((sum, item) => sum + item.price, 0);

      // お客様が支払うお金の決定
      currentPaid = calculateSmartCustomerPayment(currentTotal);
      changeNeeded = currentPaid - currentTotal;

      // 描画更新（おつり表示は自動計算せず「？？？」に）
      renderClerkCart();
      document.getElementById('display-total').textContent = currentTotal.toLocaleString();
      document.getElementById('display-paid').textContent = currentPaid.toLocaleString();
      document.getElementById('display-change-needed').textContent = '？？？';
      document.getElementById('btn-show-hint').innerHTML = '<i class="fa-solid fa-eye me-1"></i>計算の答え';

      renderCustomerPaidTray(currentPaid);
    }

    // おつり追加
    function addChangeMoney(amount) {
      if (amount >= 1000) {
        playSound('beep');
      } else {
        playSound('coin');
      }
      selectedChangeMoney.push(amount);
      updateSelectedChangeDisplay();
    }

    // おつり指定削除
    function removeChangeIndex(idx) {
      playSound('coin');
      selectedChangeMoney.splice(idx, 1);
      updateSelectedChangeDisplay();
    }

    // おつりクリア
    function clearSelectedChange() {
      playSound('coin');
      selectedChangeMoney = [];
      updateSelectedChangeDisplay();
    }

    // おつり回答チェック
    function submitChangeAnswer() {
      const currentGivenSum = selectedChangeMoney.reduce((a, b) => a + b, 0);
      const exactChange = currentPaid - currentTotal;

      if (currentGivenSum === exactChange) {
        playSound('success');
        clerkScore += 100;
        clerkStreak++;
        document.getElementById('clerk-score').textContent = clerkScore;
        document.getElementById('clerk-streak').textContent = clerkStreak;

        showModal(
          '🎉 大正解！',
          `正確なおつり <b>${exactChange.toLocaleString()} 円</b> を渡すことができました！<br>すばやい金銭処理です！`,
          true
        );
      } else {
        playSound('error');
        clerkStreak = 0;
        document.getElementById('clerk-streak').textContent = clerkStreak;

        const diff = currentGivenSum - exactChange;
        let hintMsg = '';
        if (diff < 0) {
          hintMsg = `おつりが <b>${Math.abs(diff).toLocaleString()} 円 不足</b> しています。`;
        } else {
          hintMsg = `おつりを <b>${diff.toLocaleString()} 円 多め</b> に渡しています。`;
        }

        showModal(
          '❌ もういちど計算してみよう',
          `渡した金額: ${currentGivenSum.toLocaleString()}円<br>${hintMsg}<br>正解のおつりは <b>${exactChange.toLocaleString()} 円</b> です。`,
          false
        );
      }
    }

    function toggleChangeHint() {
      isHintShown = !isHintShown;
      const displayEl = document.getElementById('display-change-needed');
      const btnEl = document.getElementById('btn-show-hint');

      if (isHintShown) {
        displayEl.textContent = changeNeeded.toLocaleString();
        btnEl.innerHTML = '<i class="fa-solid fa-eye-slash me-1"></i>隠す';
      } else {
        displayEl.textContent = '？？？';
        btnEl.innerHTML = '<i class="fa-solid fa-eye me-1"></i>計算の答え';
      }
    }

    // 店員用ミニ電卓
    function pressClerkCalc(val) {
      playSound('beep');
      if (clerkCalcInput === '0') clerkCalcInput = '';
      clerkCalcInput += val;
      document.getElementById('clerk-calc-disp').textContent = clerkCalcInput;
    }

    function clearClerkCalc() {
      playSound('beep');
      clerkCalcInput = '';
      document.getElementById('clerk-calc-disp').textContent = '0';
    }

    function calcClerkResult() {
      playSound('beep');
      try {
        // 安全な計算処理
        const sanitized = clerkCalcInput.replace(/[^0-9+\-*/.]/g, '');
        if (sanitized) {
          const res = Function(`'use strict'; return (${sanitized})`)();
          clerkCalcInput = res.toString();
          document.getElementById('clerk-calc-disp').textContent = Number(res).toLocaleString();
        }
      } catch (e) {
        document.getElementById('clerk-calc-disp').textContent = 'エラー';
        clerkCalcInput = '';
      }
    }

    function updateSelectedChangeDisplay() {
      const tray = document.getElementById('selected-change-tray');
      const sumEl = document.getElementById('current-given-change');
      const badge = document.getElementById('change-status-badge');

      const sum = selectedChangeMoney.reduce((a, b) => a + b, 0);
      sumEl.innerHTML = `${sum.toLocaleString()} <span class="text-sm">円</span>`;

      if (selectedChangeMoney.length === 0) {
        tray.innerHTML = '<span class="text-xs text-slate-400 w-full text-center py-4">下のお金をクリックしておつりをのせてね</span>';
        badge.textContent = '未準備';
        badge.className = 'text-xs font-bold px-3 py-1.5 rounded-full bg-slate-200 text-slate-600';
      } else {
        tray.innerHTML = '';
        selectedChangeMoney.forEach((val, idx) => {
          const btn = document.createElement('div');
          if (val >= 1000) {
            btn.className = `bill bill-${val} text-[10px] py-1 px-2 h-8 font-bold flex items-center justify-between gap-2 shadow-sm`;
            btn.innerHTML = `<span>${val}円</span> <i class="fa-solid fa-xmark text-slate-400 text-[10px]" onclick="removeChangeIndex(${idx})"></i>`;
          } else {
            btn.className = `coin coin-${val} text-[10px] w-9 h-9 font-bold relative`;
            btn.innerHTML = `<span>${val}</span>`;
            btn.onclick = () => removeChangeIndex(idx);
          }
          tray.appendChild(btn);
        });

        // 自動ナビ（ネタバレ）を隠し、準備中金額のみを表示
        badge.textContent = `${sum.toLocaleString()} 円セット完了`;
        badge.className = 'text-xs font-bold px-3 py-1.5 rounded-full bg-blue-100 text-blue-700 border border-blue-200';
      }
    }

    function nextClerkCustomer() {
      initClerkMode();
    }

    // ==========================================
    // 2. お客さんモード Logic
    // ==========================================
    function initCustomerShelf() {
      const container = document.getElementById('store-shelf');
      container.innerHTML = '';

      STORE_ITEMS.forEach(item => {
        const card = document.createElement('button');
        card.onclick = () => addCustomerCart(item);
        card.className = 'bg-slate-50 hover:bg-emerald-50 border border-slate-200 hover:border-convenii-green p-3 rounded-xl flex flex-col items-center gap-1.5 transition text-center group';
        card.innerHTML = `
          <span class="text-3xl group-hover:scale-110 transition-transform">${item.icon}</span>
          <span class="text-xs font-bold text-slate-700 line-clamp-1">${item.name}</span>
          <span class="text-xs font-extrabold text-convenii-green bg-white px-2 py-0.5 rounded-full border border-emerald-200">${item.price}円</span>
        `;
        container.appendChild(card);
      });
    }

    function addCustomerCart(item) {
      playSound('beep');
      custCart.push(item);
      updateCustomerCartUI();
    }

    function clearCustomerCart() {
      custCart = [];
      custPaymentMoney = [];
      updateCustomerCartUI();
      updateCustPaymentUI();
    }

    function updateCustomerCartUI() {
      const list = document.getElementById('customer-cart-list');
      const subtotalEl = document.getElementById('cust-subtotal');
      const totalEl = document.getElementById('cust-total');

      if (custCart.length === 0) {
        list.innerHTML = '<div class="text-center py-6 text-slate-400 text-xs">商品棚から食べ物や飲み物を選んでね</div>';
        subtotalEl.textContent = '0円';
        totalEl.textContent = '0円';
        document.getElementById('smart-payment-hint').classList.add('hidden');
        return;
      }

      list.innerHTML = '';
      let total = 0;
      custCart.forEach((item, index) => {
        total += item.price;
        const div = document.createElement('div');
        div.className = 'flex justify-between items-center bg-slate-50 p-2 rounded-lg text-xs font-bold';
        div.innerHTML = `
          <span>${item.icon} ${item.name}</span>
          <div class="flex items-center gap-2">
            <span>${item.price}円</span>
            <button onclick="removeCustomerCartItem(${index})" class="text-rose-500 hover:text-rose-700">
              <i class="fa-solid fa-trash-can"></i>
            </button>
          </div>
        `;
        list.appendChild(div);
      });

      subtotalEl.textContent = `${total.toLocaleString()}円`;
      totalEl.textContent = `${total.toLocaleString()}円`;

      // 賢い支払い方のヒント表示
      generateSmartPaymentHint(total);
    }

    function removeCustomerCartItem(index) {
      custCart.splice(index, 1);
      updateCustomerCartUI();
    }

    function generateSmartPaymentHint(total) {
      const hintBox = document.getElementById('smart-payment-hint');
      const hintText = document.getElementById('hint-text');

      if (total === 0) {
        hintBox.classList.add('hidden');
        return;
      }

      hintBox.classList.remove('hidden');

      const rem10 = total % 10;
      const rem100 = total % 100;
      let tipsHtml = '';

      // ケース1: 1円・5円など1桁の端数がある場合（例: 348円, 163円）
      if (rem10 !== 0) {
        const roundUp10 = Math.ceil(total / 10) * 10; // 例: 350円
        const billBase = total <= 500 ? 500 : 1000;
        const smartExactEnd = billBase + rem100; // 例: 1048円

        tipsHtml = `
          <div class="space-y-1.5">
            <div class="font-bold text-amber-900 flex items-center gap-1">
              <i class="fa-solid fa-wand-magic-sparkles text-amber-500"></i>
              <span>小銭（1円玉・5円玉）を減らすスマート技！</span>
            </div>
            <div class="bg-white p-2 rounded-lg border border-amber-200 space-y-1 text-slate-700">
              <div>💡 <b>${roundUp10}円</b> を出せば、おつりはたったの <b>${roundUp10 - total}円</b> に！</div>
              ${total >= 100 ? `<div>💡 <b>${smartExactEnd}円</b>（端数${rem100}円を合わせる）を出すと、おつりが <b>${smartExactEnd - total}円</b>（お札・500円玉）でスッキリ！</div>` : ''}
            </div>
          </div>
        `;
      } 
      // ケース2: 10円単位の端数がある場合（例: 780円, 420円, 260円）
      else if (rem100 !== 0) {
        if (rem100 >= 50) {
          // 例: 780円 -> 1,030円出すとおつり250円！
          const baseBill = Math.ceil(total / 500) * 500;
          const smartAmount = baseBill + (rem100 - 50); 
          const change = smartAmount - total;

          tipsHtml = `
            <div class="space-y-1.5">
              <div class="font-bold text-amber-900 flex items-center gap-1">
                <i class="fa-solid fa-wand-magic-sparkles text-amber-500"></i>
                <span>おつりを50円玉・お札にまとめる技！</span>
              </div>
              <div class="bg-white p-2 rounded-lg border border-amber-200 text-slate-700">
                💡 <b>${total}円</b> に対して <b>${smartAmount}円</b>（お札＋${rem100 - 50}円）を出すと、おつりが <b>${change}円</b>（50円玉や100円玉）になって小銭が激減します！
              </div>
            </div>
          `;
        } else {
          // 例: 420円 -> 520円出すとおつり100円！
          const baseBill = Math.ceil(total / 500) * 500;
          const smartAmount = baseBill + rem100;
          const change = smartAmount - total;

          tipsHtml = `
            <div class="space-y-1.5">
              <div class="font-bold text-amber-900 flex items-center gap-1">
                <i class="fa-solid fa-wand-magic-sparkles text-amber-500"></i>
                <span>端数を合わせておつりをキリ良くする技！</span>
              </div>
              <div class="bg-white p-2 rounded-lg border border-amber-200 text-slate-700">
                💡 <b>${total}円</b> に対して <b>${smartAmount}円</b>（端数${rem100}円を加える）を出すと、おつりがピッタリ <b>${change}円</b> 玉1枚（またはお札）で戻ってきます！
              </div>
            </div>
          `;
        }
      } 
      // ケース3: ぴったり100円単位（例: 500円, 700円）
      else {
        const nextBill = Math.ceil((total + 1) / 1000) * 1000;
        tipsHtml = `
          <div class="text-slate-700">
            💡 <b>${total}円</b> はぴったりキリの良い金額です。<b>${total}円</b> をちょうど出すか、<b>${nextBill}円札</b> でお会計しましょう！
          </div>
        `;
      }

      hintText.innerHTML = tipsHtml;
    }

    function addCustPayment(amount) {
      playSound('coin');
      custPaymentMoney.push(amount);
      updateCustPaymentUI();
    }

    function clearCustPayment() {
      custPaymentMoney = [];
      updateCustPaymentUI();
    }

    function updateCustPaymentUI() {
      const tray = document.getElementById('cust-pay-tray');
      const sumEl = document.getElementById('cust-payment-sum');
      const sum = custPaymentMoney.reduce((a, b) => a + b, 0);

      sumEl.textContent = `出す金額: ${sum.toLocaleString()}円`;

      if (custPaymentMoney.length === 0) {
        tray.innerHTML = '<span class="text-xs text-slate-400 w-full text-center">下のお金をクリックして出す</span>';
      } else {
        tray.innerHTML = '';
        custPaymentMoney.forEach((val, idx) => {
          const chip = document.createElement('span');
          chip.className = 'bg-white border text-xs px-2 py-1 rounded font-bold shadow-sm flex items-center gap-1 cursor-pointer';
          chip.innerHTML = `${val}円 <i class="fa-solid fa-xmark text-slate-400 text-[10px]"></i>`;
          chip.onclick = () => {
            custPaymentMoney.splice(idx, 1);
            updateCustPaymentUI();
          };
          tray.appendChild(chip);
        });
      }
    }

    function submitCustomerPay() {
      const total = custCart.reduce((sum, item) => sum + item.price, 0);
      const paid = custPaymentMoney.reduce((a, b) => a + b, 0);

      if (total === 0) {
        alert('まず商品を選んでカゴに入れてね！');
        return;
      }

      if (paid < total) {
        playSound('error');
        alert(`お金が不足しています！（合計: ${total}円 / 出した額: ${paid}円）`);
        return;
      }

      const change = paid - total;
      playSound('success');
      showModal('🛒 お買い上げありがとうございます！', `合計 ${total}円 のお買い物をしました。<br>お預かり: ${paid}円<br><b>おつり: ${change}円</b> を受け取りました！`, true);

      clearCustomerCart();
    }

    // ==========================================
    // 3. 金銭＆両替ドリル Logic
    // ==========================================
    const DRILL_QUESTIONS = [
      {
        category: '両替の考え方',
        q: '1,000円札 1枚 を、すべて100円玉に両替すると 何枚 になりますか？',
        options: ['5枚', '10枚', '50枚', '100枚'],
        correctIndex: 1,
        explanation: '1000 ÷ 100 ＝ 10枚 です。100円玉が10枚で1000円になります！'
      },
      {
        category: 'おつりの計算',
        q: '420円 のお弁当を買うために 500円玉 を出しました。おつりはいくらですか？',
        options: ['60円', '80円', '120円', '180円'],
        correctIndex: 1,
        explanation: '500 － 420 ＝ 80円 です！'
      },
      {
        category: '両替の考え方',
        q: '500円玉 1枚 は、50円玉 何枚 と同じ金額ですか？',
        options: ['5枚', '10枚', '20枚', '50枚'],
        correctIndex: 1,
        explanation: '500 ÷ 50 ＝ 10枚 です。50円玉10枚で500円になります！'
      },
      {
        category: '賢い支払い方',
        q: '780円 の買い物をするとき、1,030円（1000円札1枚＋10円玉3枚）を出すと、おつりはいくら？',
        options: ['200円', '250円', '300円', '350円'],
        correctIndex: 1,
        explanation: '1030 － 780 ＝ 250円！端数の30円を出したことで小銭が出ず綺麗な250円になります。'
      },
      {
        category: '最少枚数計算',
        q: '680円 をお札と小銭でピッタリ作る時、一番少ない枚数は何枚？ (500円x1, 100円x1, 50円x1, 10円x3)',
        options: ['4枚', '6枚', '8枚', '10枚'],
        correctIndex: 1,
        explanation: '500円(1) + 100円(1) + 50円(1) + 10円(3) = 計 6枚 です！'
      }
    ];

    function loadDrillQuestion() {
      const qData = DRILL_QUESTIONS[drillIndex];
      document.getElementById('drill-category').textContent = qData.category;
      document.getElementById('drill-q-num').textContent = `第 ${drillIndex + 1} / ${DRILL_QUESTIONS.length} 問`;
      document.getElementById('drill-question-text').textContent = qData.q;

      const optsContainer = document.getElementById('drill-answers-container');
      optsContainer.innerHTML = '';

      qData.options.forEach((optText, idx) => {
        const btn = document.createElement('button');
        btn.className = 'drill-opt-btn bg-slate-50 hover:bg-purple-50 border-2 border-slate-200 hover:border-purple-400 font-bold p-4 rounded-2xl text-slate-800 text-lg transition text-center shadow-sm';
        btn.textContent = optText;
        btn.onclick = () => checkDrillAnswer(idx);
        optsContainer.appendChild(btn);
      });

      document.getElementById('drill-feedback').classList.add('hidden');
      document.getElementById('drill-next-btn').classList.add('hidden');
    }

    function checkDrillAnswer(selectedIdx) {
      const qData = DRILL_QUESTIONS[drillIndex];
      const feedback = document.getElementById('drill-feedback');
      const optBtns = document.querySelectorAll('.drill-opt-btn');

      optBtns.forEach(b => b.disabled = true);

      if (selectedIdx === qData.correctIndex) {
        playSound('success');
        drillScoreCount++;
        feedback.className = 'p-4 rounded-xl text-center font-bold text-sm bg-emerald-100 text-emerald-800 border border-emerald-300';
        feedback.innerHTML = `🎉 大正解！<br><span class="font-normal">${qData.explanation}</span>`;
      } else {
        playSound('error');
        feedback.className = 'p-4 rounded-xl text-center font-bold text-sm bg-rose-100 text-rose-800 border border-rose-300';
        feedback.innerHTML = `❌ 残念！正解は「${qData.options[qData.correctIndex]}」でした。<br><span class="font-normal">${qData.explanation}</span>`;
      }

      feedback.classList.remove('hidden');
      document.getElementById('drill-score').textContent = `${drillScoreCount} / ${DRILL_QUESTIONS.length}`;
      document.getElementById('drill-next-btn').classList.remove('hidden');
    }

    function nextDrillQuestion() {
      drillIndex = (drillIndex + 1) % DRILL_QUESTIONS.length;
      loadDrillQuestion();
    }

    // ==========================================
    // 4. 自由レジ＆両替シミュレーター Logic
    // ==========================================
    function setFreeField(field) {
      activeFreeField = field;
      document.getElementById('btn-field-total').className = field === 'total' 
        ? 'flex-1 py-2 px-3 rounded-lg text-xs font-bold border-2 border-teal-500 bg-teal-50 text-teal-800'
        : 'flex-1 py-2 px-3 rounded-lg text-xs font-bold border border-slate-200 bg-slate-50 text-slate-600';

      document.getElementById('btn-field-paid').className = field === 'paid' 
        ? 'flex-1 py-2 px-3 rounded-lg text-xs font-bold border-2 border-teal-500 bg-teal-50 text-teal-800'
        : 'flex-1 py-2 px-3 rounded-lg text-xs font-bold border border-slate-200 bg-slate-50 text-slate-600';
    }

    function pressNumpad(num) {
      playSound('beep');
      if (activeFreeField === 'total') {
        freeTotal = parseInt(`${freeTotal}${num}`) || 0;
      } else {
        freePaid = parseInt(`${freePaid}${num}`) || 0;
      }
      updateFreeRegisterDisplay();
    }

    function clearNumpad() {
      playSound('beep');
      if (activeFreeField === 'total') freeTotal = 0;
      else freePaid = 0;
      updateFreeRegisterDisplay();
    }

    function updateFreeRegisterDisplay() {
      document.getElementById('free-total-disp').textContent = `${freeTotal.toLocaleString()} 円`;
      document.getElementById('free-paid-disp').textContent = `${freePaid.toLocaleString()} 円`;

      const change = freePaid - freeTotal;
      document.getElementById('free-change-disp').textContent = `${(change > 0 ? change : 0).toLocaleString()} 円`;
    }

    function demonstrateExchange(amount) {
      playSound('coin');
      const box = document.getElementById('exchange-result-box');
      box.innerHTML = '';

      let breakdownText = '';
      let coinsHTML = '';

      if (amount === 1000) {
        breakdownText = '1,000円札 1枚 は 100円玉 10枚 に分解（両替）できます！';
        for (let i = 0; i < 10; i++) {
          coinsHTML += `<div class="coin coin-100 w-9 h-9 text-[10px]">100</div>`;
        }
      } else if (amount === 500) {
        breakdownText = '500円玉 1枚 は 100円玉 5枚 に分解（両替）できます！';
        for (let i = 0; i < 5; i++) {
          coinsHTML += `<div class="coin coin-100 w-9 h-9 text-[10px]">100</div>`;
        }
      } else if (amount === 100) {
        breakdownText = '100円玉 1枚 は 10円玉 10枚 に分解できます！';
        for (let i = 0; i < 10; i++) {
          coinsHTML += `<div class="coin coin-10 w-8 h-8 text-[10px]">10</div>`;
        }
      } else if (amount === 50) {
        breakdownText = '50円玉 1枚 は 10円玉 5枚 に分解できます！';
        for (let i = 0; i < 5; i++) {
          coinsHTML += `<div class="coin coin-10 w-8 h-8 text-[10px]">10</div>`;
        }
      } else if (amount === 10) {
        breakdownText = '10円玉 1枚 は 1円玉 10枚 に分解できます！';
        for (let i = 0; i < 10; i++) {
          coinsHTML += `<div class="coin coin-1 w-7 h-7 text-[9px]">1</div>`;
        }
      }

      box.innerHTML = `
        <div class="text-xs font-bold text-amber-900 mb-3">${breakdownText}</div>
        <div class="flex flex-wrap gap-2 justify-center items-center">
          ${coinsHTML}
        </div>
      `;
    }

    // Modal Display
    function showModal(title, message, isSuccess) {
      const modal = document.getElementById('modal-result');
      const icon = document.getElementById('modal-icon');
      document.getElementById('modal-title').textContent = title;
      document.getElementById('modal-msg').innerHTML = message;

      if (isSuccess) {
        icon.className = 'w-16 h-16 bg-emerald-100 text-convenii-green rounded-full flex items-center justify-center text-3xl';
        icon.innerHTML = '<i class="fa-solid fa-circle-check"></i>';
      } else {
        icon.className = 'w-16 h-16 bg-rose-100 text-rose-600 rounded-full flex items-center justify-center text-3xl';
        icon.innerHTML = '<i class="fa-solid fa-circle-xmark"></i>';
      }

      modal.classList.remove('hidden');
    }

    function closeModal() {
      document.getElementById('modal-result').classList.add('hidden');
      if (currentMode === 'clerk') {
        initClerkMode();
      }
    }
  </script>
</body>
</html>
