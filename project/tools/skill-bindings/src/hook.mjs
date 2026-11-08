export async function resolve(specifier, context, next) {
  try {
    return await next(specifier, context);
  } catch (err) {
    if (!specifier.endsWith(".ts") && !specifier.startsWith("node:")) {
      for (const cand of [`${specifier}.ts`, `${specifier}/index.ts`]) {
        try {
          return await next(cand, context);
        } catch {
          /* try next */
        }
      }
    }
    throw err;
  }
}
