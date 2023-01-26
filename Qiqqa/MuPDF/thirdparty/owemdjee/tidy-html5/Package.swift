// swift-tools-version:5.3
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

#if swift(>=5.2)
let provider: [SystemPackageProvider] = [
    .apt(["tidy-html5"])
]
#else
let provider: [SystemPackageProvider] = [
    .apt(["tidy-html5"]),
    .brew(["tidy-html5"])
]
#endif

let cSettings: [CSetting] = [
    .headerSearchPath("include")
]

let package = Package(
    name: "TidyHTML5",
    products: [
        .library(
            name: "TidyHTML5",
            targets: ["TidyHTML5"]),
    ],
    targets: [
        // Targets are the basic building blocks of a package. A target can define a module or a test suite.
        // Targets can depend on other targets in this package, and on products in packages which this package depends on.
        .systemLibrary(name: "tidy-html5", path: "Modules", pkgConfig: "tidy", providers: provider),
        .target(name: "TidyHTML5",
                dependencies: ["tidy-html5"],
                path: ".",
                exclude: [],
                sources: ["src"],
                publicHeadersPath: "include",
                cSettings: cSettings,
                cxxSettings: [CXXSetting.define("-mmacosx-version-min", to: "10.14")],
                swiftSettings: nil,
                linkerSettings: nil)
    ],
    swiftLanguageVersions: [.v5]
)

