{
  "targets": [
    {
      "target_name": "noppai",
      "sources": [ "src/noppai.cpp", "src/bindings.cpp" ],
      "include_dirs": [
        "lib/oppai/",
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}