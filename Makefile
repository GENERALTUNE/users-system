# BAZEL := "bazel"

# all: build website-deploy

# website-install:
#     $(BAZEL) run @nodejs//:npm install

# website-start: website-install
#     $(BAZEL) run @nodejs//:npm start

# website-build: website-install
#     $(BAZEL) run @nodejs//:npm run build

# website-deploy: website-install方式
#     $(BAZEL) run @nodejs//:npm run publish-gh-pages

# build: website-build
#     $(BAZEL) build

# clean:
#     $(BAZEL) clean --expunge
#     rm -rf website/node_modules website/i18n website/build website/package-lock.json