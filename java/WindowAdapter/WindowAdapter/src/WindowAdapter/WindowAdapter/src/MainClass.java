// パッケージ・クラスのインポート
import java.awt.Frame;	// Frameクラス(java.awtパッケージ)
import java.awt.event.WindowAdapter;	// WindowAdapterクラス(java.awt.eventパッケージ)
import java.awt.event.WindowEvent;		// WindowEventクラス(java.awt.eventパッケージ)

// メインクラス
public class MainClass {	// MainClassの定義

	// Javaのエントリポイント
	public static void main(String[] args){	// mainメソッドの定義

		// フレームの生成
		Frame frame = new Frame();	// Frameオブジェクトを生成し, frameに格納.

		// サイズのセット.
		frame.setSize(640, 480);	// setSizeでサイズを(640, 480)にセット.

		// 表示状態のセット.
		frame.setVisible(true);	// setVisibleで表示状態をtrueにセット.

		// ウィンドウリスナーのセット.
		frame.addWindowListener(new WindowAdapter(){	// WindowAdapterを継承した匿名クラスとしてアダプタを定義し, 引数としてaddWindowListenerに渡す.

			// windowClosedとwindowClosingのみオーバーライド. それ以外はWindowAdapterに既定の動作が定義されている.
			// ウィンドウが閉じられた時.
			public void windowClosed(WindowEvent e){	// windowClosedの定義

				// アプリケーションの終了
				System.exit(0);	// System.exit(0)でアプリケーションを終了.

			}

			// ウィンドウが閉じられている時.
			public void windowClosing(WindowEvent e){	// windowClosingの定義

				// ウィンドウリソースの開放
				e.getWindow().dispose();	// e.getWindowでWindowが取得できるので, そのWindowをdisposeで破棄する.

			}

		});

	}

}