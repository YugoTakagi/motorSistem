cmake_minimum_required(VERSION 3.17)
project(Lib
    VERSION 1.0.0
    LANGUAGES CXX
)

# 1. INTERFACE_INCLUDE_DIRECTORIES にソースディレクトリとビルドディレクトリを自動追加する。
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON) 

# 2. ライブラリのビルド指定
add_library(Lim STATIC
     ./src/Tcp_Ip.cxx
)

# 3. インストールするヘッダファイルを指定しておく。
# 指定したファイルは、INSTALL(TARGETS) の PUBLIC_HEADER で指定した
# ディレクトリにインストールされる。
set_target_properties(Lim PROPERTIES
        PUBLIC_HEADER Lim/inc/Tcp_Ip.hpp
)

# 4. foo ライブラリが依存するライブラリを指定する。（オプション）
# PUBLIC指定してリンクすると、依存ライブラリがエクスポートされる(注1)
# target_link_libararies(foo PUBLIC bar)

# 5. ターゲットのインストール指定
install(TARGETS Lim
    EXPORT Lib-export                     # 5.a EXPORT オプションで エクスポート名を指定する
    LIBRARY        DESTINATION lim        # 5.b ライブラリのインストール先
    INCLUDES       DESTINATION inc        # 5.c エクスポート時にincludeパスに含めるパスを指定する
    PUBLIC_HEADER  DESTINATION inc/Lim)   # ヘッダのインストール先

# 6. foo-config.cmake を自動生成してインストールする。 
install(EXPORT Lim-export                     # 6.a 
    FILE Lim-config.cmake                     # 6.b ファイル名を指定する
    DESTINATION share/cmake/Lim/              # 6.c インストール先
    EXPORT_LINK_INTERFACE_LIBRARIES)          # 6.d 同時にリンクすべきライブラリをエクスポートする