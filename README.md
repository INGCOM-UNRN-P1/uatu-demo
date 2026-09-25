# uatu-demo — Examen práctico supervisado con uatu

Repositorio de demostración de un examen de Programación I supervisado con
[uatu](https://github.com/INGCOM-UNRN-P1/uatu). Sirve como plantilla para
armar un examen real: contiene la consigna, el código inicial, el manifiesto
firmado `.uatu.conf`, el registro de claves docentes y el workflow de
evaluación forense.

## Consigna

Completar en `src/ejercicio.c` las funciones declaradas en `src/ejercicio.h`:

| Función | Descripción |
|---|---|
| `int fibonacci(int n)` | n-ésimo número de Fibonacci, con `fibonacci(0) == 0`. |
| `bool es_primo(int n)` | Indica si `n` es primo (los menores que 2 no lo son). |
| `int invertir_digitos(int n)` | `n` con los dígitos invertidos: `invertir_digitos(1230) == 321`. |

```bash
make test
```

Entregar con commits y `git push` sobre `main` antes del cierre del examen.

## Para el estudiante: supervisión durante el examen

1. Instalar la extensión uatu:

   ```bash
   curl -LO https://github.com/INGCOM-UNRN-P1/uatu/releases/latest/download/uatu.vsix
   code --install-extension uatu.vsix
   ```

2. Abrir este repositorio en VS Code. La barra de estado muestra el estado
   de la supervisión:

   | Indicador | Significado |
   |---|---|
   | `$(clock) Uatu: Esperando inicio (HH:mm UTC)` | El examen todavía no comenzó. |
   | `$(shield) Uatu: @usuario (Lote: B, Eventos: N)` | Sesión activa. |
   | `$(check) Uatu: Examen Concluido` | Terminó la ventana del examen. |

3. Al comenzar la ventana, iniciar sesión con GitHub y aceptar el aviso de
   *Fair Play*. Desde ese momento se registran los pegados e inserciones
   masivas (su contenido viaja **cifrado** y solo la cátedra puede leerlo),
   las pérdidas de foco de VS Code y las extensiones no permitidas.

La telemetría se guarda en la rama `uatu-audit/<usuario>/<sesión>` de este
repositorio. No modifica los archivos, el index ni los commits del estudiante.
Durante el examen no están permitidas GitHub Copilot, Continue, Codeium ni
Tabnine.

Ventana de esta demo: **2026-09-25 00:00 UTC** al **2026-10-31 23:59:59 UTC**.

## Para la cátedra

### Piezas del examen

| Archivo | Rol |
|---|---|
| `.uatu.conf` | Manifiesto del examen (ventana, umbrales, extensiones prohibidas), firmado con la clave Ed25519 del docente `demo-p1-2026`. |
| `keys.json` | Registro de claves docentes, firmado por la raíz institucional `inicial_unrn` que viene embebida en la extensión. La extensión lo descarga de `raw.githubusercontent.com` (ver `auth.public_key_registry_url`). |
| `.github/workflows/uatu-audit.yml` | Evaluación forense a demanda con `uatu-audit`. |

Las herramientas docentes se instalan con:

```bash
uv tool install "git+https://github.com/INGCOM-UNRN-P1/uatu-tools"
```

### Cambiar la ventana u otras reglas

Cualquier cambio en `.uatu.conf` invalida la firma. Después de editarlo hay
que volver a firmarlo:

```bash
uatu-admin sign-config --config .uatu.conf \
    --key ~/.config/uatu/claves/demo-p1-2026.ed25519.pem --key-id demo-p1-2026
uatu-admin verify-config --config .uatu.conf \
    --verify-key ab53e4392cecf143dba71b76aa9468d7cf1d57a4dceeececcf87f5a5545ecb18
```

Para un examen real conviene generar claves propias (`uatu-admin keygen`),
agregarlas al registro institucional y firmarlo con la raíz
(`uatu-admin registry-add` y `registry-sign`). El registro puede publicarse
en cualquier URL HTTPS, porque la firma raíz lo protege.

### Evaluación forense

Configurar en el repositorio los secretos:

- `UATU_TEACHER_PUBLIC_KEY`: `ab53e4392cecf143dba71b76aa9468d7cf1d57a4dceeececcf87f5a5545ecb18`
- `UATU_TEACHER_PRIVATE_KEY`: contenido de `~/.config/uatu/claves/demo-p1-2026.x25519.pem`

y ejecutar el workflow *Evaluación Forense Uatu* (para todos o para un
usuario). Localmente:

```bash
git fetch origin '+refs/heads/uatu-audit/*:refs/remotes/origin/uatu-audit/*'
uatu-audit --repo . \
    --teacher-key ab53e4392cecf143dba71b76aa9468d7cf1d57a4dceeececcf87f5a5545ecb18 \
    --decrypt-key ~/.config/uatu/claves/demo-p1-2026.x25519.pem \
    --md-out reporte.md
```

Códigos de salida: `0` sin anomalías, `1` falla de integridad, `2` alertas
heurísticas (pegados masivos, inserciones externas, extensiones prohibidas).

Para evitar la manipulación de la telemetría, agregar una regla de protección
de ramas sobre `uatu-audit/**` que impida el force-push y el borrado.
